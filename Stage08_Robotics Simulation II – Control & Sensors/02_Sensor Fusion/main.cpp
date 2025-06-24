#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <iomanip>

using namespace std;

// Simulated IR sensor readings with noise
struct SensorData {
    double frontLeft;
    double frontRight;
    double sideLeft;
    double sideRight;
};

class CorridorNavigator {
private:
    // Position and orientation
    double position;  // Lateral position in corridor (-1.0 = left wall, 1.0 = right wall)
    double heading;   // Angle relative to corridor centerline (radians)
    
    // Sensor parameters
    const double SENSOR_NOISE = 0.05;
    const double CORRIDOR_WIDTH = 2.0; // Total width in meters
    
    // Control parameters
    const double KP_CENTER = 0.5;  // Proportional gain for centering
    const double KP_ALIGN = 0.3;   // Proportional gain for alignment
    const double MOVE_SPEED = 0.1;
    
    // Random number generation
    mt19937 rng;
    normal_distribution<double> dist;
    
    // Add Gaussian noise to sensor readings
    double addNoise(double value) {
        return max(0.0, min(1.0, value + dist(rng) * SENSOR_NOISE));
    }
    
public:
    CorridorNavigator() : position(0.0), heading(0.0), 
                         rng(random_device()()), dist(0.0, 1.0) {}
    
    // Simulate sensor readings based on current position
    SensorData readSensors() {
        SensorData sensors;
        
        // Calculate true distances to walls
        double leftWallDist = 1.0 + position;  // 0 to 2
        double rightWallDist = 1.0 - position; // 0 to 2
        
        // Front sensors detect walls when too close or misaligned
        sensors.frontLeft = addNoise(exp(-leftWallDist * (1.0 + sin(heading))));
        sensors.frontRight = addNoise(exp(-rightWallDist * (1.0 - sin(heading))));
        
        // Side sensors detect lateral distance
        sensors.sideLeft = addNoise(1.0 - leftWallDist/2.0);
        sensors.sideRight = addNoise(1.0 - rightWallDist/2.0);
        
        return sensors;
    }
    
    // Fuse sensor data and calculate control outputs
    void update(const SensorData& sensors) {
        // 1. Calculate alignment error from front sensors
        double alignError = sensors.frontRight - sensors.frontLeft;
        
        // 2. Calculate position error from side sensors
        double posError = sensors.sideRight - sensors.sideLeft;
        
        // 3. Combined control law
        double steer = KP_ALIGN * alignError + KP_CENTER * posError;
        
        // Update position and heading (simplified kinematics)
        heading += steer;
        position += tan(heading) * MOVE_SPEED;
        
        // Keep position within corridor bounds
        position = max(-1.0, min(1.0, position));
        
        // Dampen heading changes
        heading *= 0.8;
    }
    
    // Display current status
    void display(const SensorData& sensors) const {
        const int width = 60;
        int robotPos = static_cast<int>((position + 1.0) * width / 2.0);
        robotPos = max(0, min(width-1, robotPos));
        
        cout << "\033[2J\033[1;1H"; // Clear screen
        cout << "Corridor Navigation with Sensor Fusion (Ctrl+C to exit)\n";
        cout << fixed << setprecision(3);
        cout << "Position: " << setw(6) << position << "  ";
        cout << "Heading: " << setw(6) << heading << "\n";
        
        cout << "Sensors - Front: L=" << sensors.frontLeft << " R=" << sensors.frontRight;
        cout << "  Side: L=" << sensors.sideLeft << " R=" << sensors.sideRight << "\n\n";
        
        cout << "|";
        for (int i = 0; i < width; i++) {
            if (i == robotPos) {
                // Show robot direction
                if (heading > 0.1) cout << ">";
                else if (heading < -0.1) cout << "<";
                else cout << "O";
            } else if (i == 0 || i == width-1) {
                cout << "|"; // Walls
            } else {
                cout << " ";
            }
        }
        cout << "|\n";
    }
};

int main() {
    CorridorNavigator robot;
    
    cout << "Corridor Navigation Simulation\n";
    cout << "Starting in 1 second...\n";
    this_thread::sleep_for(chrono::seconds(1));
    
    // Main control loop
    while (true) {
        SensorData sensors = robot.readSensors();
        robot.update(sensors);
        robot.display(sensors);
        this_thread::sleep_for(chrono::milliseconds(100)); // 10 FPS
    }
    
    return 0;
}