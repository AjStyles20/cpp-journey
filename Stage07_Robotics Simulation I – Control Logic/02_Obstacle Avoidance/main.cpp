#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h> // for usleep

using namespace std;

// Simulated distance sensor
class DistanceSensor {
private:
    double noiseLevel; // Sensor noise (0 = perfect)

public:
    DistanceSensor(double noise = 0.1) : noiseLevel(noise) {
        srand(time(0));
    }

    // Simulate distance reading to nearest obstacle
    double getDistance(double x, double y, double heading, const vector<pair<double, double>>& obstacles) {
        double minDistance = 100.0; // Maximum detection range
        
        for (const auto& obs : obstacles) {
            // Calculate angle to obstacle
            double dx = obs.first - x;
            double dy = obs.second - y;
            double angleToObstacle = atan2(dy, dx);
            double angleDiff = fmod(angleToObstacle - heading + M_PI, 2*M_PI) - M_PI;
            
            // Only consider obstacles in front (within 60 degree cone)
            if (fabs(angleDiff) < M_PI/3) {
                double distance = sqrt(dx*dx + dy*dy);
                if (distance < minDistance) {
                    minDistance = distance;
                }
            }
        }
        
        // Add Gaussian noise
        if (minDistance < 100.0) {
            double noise = (rand() % 1000 - 500) / 500.0 * noiseLevel;
            minDistance += noise;
            if (minDistance < 0) minDistance = 0;
        }
        
        return minDistance;
    }
};

// Simulated robot
class ObstacleAvoidanceRobot {
private:
    double x, y;           // Position
    double heading;        // Facing direction (radians)
    double speed;          // Forward speed
    double turnRate;       // Turning speed
    double safeDistance;   // Minimum distance before avoiding
    
public:
    ObstacleAvoidanceRobot(double startX, double startY) :
        x(startX), y(startY), heading(0), speed(0.1), turnRate(M_PI/8), safeDistance(1.0) {}
    
    // Update robot position and behavior
    void update(double distanceReading) {
        // Basic obstacle avoidance logic
        if (distanceReading < safeDistance) {
            // Obstacle detected - turn right
            heading += turnRate;
            cout << "Obstacle detected! Turning right...\n";
        } else {
            // No obstacle - move forward
            x += speed * cos(heading);
            y += speed * sin(heading);
        }
    }
    
    // Get current position and heading
    tuple<double, double, double> getPose() const {
        return {x, y, heading};
    }
};

// Visualize the robot and environment
void display(double robotX, double robotY, double heading, 
             const vector<pair<double, double>>& obstacles,
             double sensorReading) {
    const int width = 60;
    const int height = 20;
    
    // Clear screen (Unix-like systems)
    cout << "\033[2J\033[1;1H";
    
    cout << "Obstacle Avoidance Robot Simulation (Ctrl+C to exit)\n";
    cout << "Sensor Reading: " << fixed << setprecision(2) << sensorReading << "\n\n";
    
    for (int iy = 0; iy < height; iy++) {
        double worldY = (height/2 - iy) * 0.5;
        for (int ix = 0; ix < width; ix++) {
            double worldX = (ix - width/2) * 0.5;
            
            // Check if this cell is the robot
            if (fabs(worldX - robotX) < 0.3 && fabs(worldY - robotY) < 0.3) {
                // Show robot direction
                double angle = fmod(heading + M_PI/4, 2*M_PI);
                if (angle < M_PI/2) cout << "^";
                else if (angle < M_PI) cout << "<";
                else if (angle < 3*M_PI/2) cout << "v";
                else cout << ">";
                continue;
            }
            
            // Check if this cell is an obstacle
            bool isObstacle = false;
            for (const auto& obs : obstacles) {
                if (fabs(worldX - obs.first) < 0.4 && fabs(worldY - obs.second) < 0.4) {
                    isObstacle = true;
                    break;
                }
            }
            
            cout << (isObstacle ? "█" : " ");
        }
        cout << "\n";
    }
    cout << "\nLegend: ^>v< = Robot (facing direction), █ = Obstacle\n";
    cout.flush();
}

int main() {
    // Set up environment with obstacles
    vector<pair<double, double>> obstacles = {
        {3.0, 2.0}, {-2.0, -1.0}, {5.0, -3.0}, {-4.0, 3.0}, {1.0, 4.0}
    };
    
    // Create robot and sensor
    ObstacleAvoidanceRobot robot(0.0, 0.0);
    DistanceSensor sensor;
    
    cout << "Obstacle Avoidance Robot Simulation\n";
    cout << "Initializing...\n";
    usleep(1000000);
    
    while (true) {
        // Get robot position and heading
        auto [x, y, heading] = robot.getPose();
        
        // Get sensor reading
        double distance = sensor.getDistance(x, y, heading, obstacles);
        
        // Update robot behavior
        robot.update(distance);
        
        // Display current state
        display(x, y, heading, obstacles, distance);
        
        // Control simulation speed
        usleep(200000); // 200ms delay
    }
    
    return 0;
}