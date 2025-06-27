#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
#include <thread>
#include <random>

using namespace std;

// Constants
const double MAX_SPEED = 5.0;  // m/s
const double SAFE_DISTANCE = 2.0;  // meters
const double ARRIVAL_THRESHOLD = 0.5;  // meters
const double CONTROL_LOOP_HZ = 10.0;  // Control frequency

// 2D Point structure
struct Point {
    double x;
    double y;
    
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    double distanceTo(const Point& other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
};

// Sensor Interface
class Sensor {
public:
    virtual Point getCurrentPosition() = 0;
    virtual vector<Point> detectObstacles() = 0;
    virtual ~Sensor() {}
};

// Simulated GPS Sensor
class GPSSensor : public Sensor {
private:
    Point currentPos;
    double noiseStdDev;
    default_random_engine generator;
    normal_distribution<double> distribution;
    
public:
    GPSSensor(Point startPos, double noise = 0.1) 
        : currentPos(startPos), noiseStdDev(noise), 
          distribution(0.0, noiseStdDev) {}
    
    Point getCurrentPosition() override {
        // Add simulated Gaussian noise
        Point noisyPos(
            currentPos.x + distribution(generator),
            currentPos.y + distribution(generator)
        );
        return noisyPos;
    }
    
    vector<Point> detectObstacles() override {
        return {};  // GPS doesn't detect obstacles
    }
    
    void updateTruePosition(Point newPos) {
        currentPos = newPos;
    }
};

// Simulated Lidar Sensor
class LidarSensor : public Sensor {
private:
    Point currentPos;
    vector<Point> obstacles;
    
public:
    LidarSensor(Point startPos) : currentPos(startPos) {
        // Generate some random obstacles
        obstacles = {
            Point(3, 4),
            Point(7, 2),
            Point(5, 8)
        };
    }
    
    Point getCurrentPosition() override {
        return currentPos;  // Lidar doesn't provide position
    }
    
    vector<Point> detectObstacles() override {
        // Simulate detection within 5m range
        vector<Point> nearbyObstacles;
        for (const auto& obs : obstacles) {
            if (currentPos.distanceTo(obs) < 5.0) {
                nearbyObstacles.push_back(obs);
            }
        }
        return nearbyObstacles;
    }
    
    void updateTruePosition(Point newPos) {
        currentPos = newPos;
    }
};

// Navigation Controller
class NavigationController {
private:
    Point target;
    Sensor& positionSensor;
    Sensor& obstacleSensor;
    
public:
    NavigationController(Point target, Sensor& posSensor, Sensor& obsSensor)
        : target(target), positionSensor(posSensor), obstacleSensor(obsSensor) {}
    
    // Calculate required velocity to reach target
    Point calculateVelocityCommand(const Point& currentPos) {
        Point direction(
            target.x - currentPos.x,
            target.y - currentPos.y
        );
        
        double distance = currentPos.distanceTo(target);
        if (distance < ARRIVAL_THRESHOLD) {
            return Point(0, 0);  // We've arrived
        }
        
        // Normalize direction and scale by speed
        if (distance > 0) {
            direction.x /= distance;
            direction.y /= distance;
        }
        
        // Simple proportional control
        double speed = min(MAX_SPEED, distance * 0.5);
        return Point(direction.x * speed, direction.y * speed);
    }
    
    // Check for obstacles and adjust path if needed
    Point avoidObstacles(const Point& currentPos, const Point& desiredVelocity) {
        auto obstacles = obstacleSensor.detectObstacles();
        if (obstacles.empty()) return desiredVelocity;
        
        Point adjustedVelocity = desiredVelocity;
        
        for (const auto& obs : obstacles) {
            double distToObs = currentPos.distanceTo(obs);
            if (distToObs < SAFE_DISTANCE) {
                // Calculate repulsion vector
                Point repulsion(
                    currentPos.x - obs.x,
                    currentPos.y - obs.y
                );
                
                // Normalize and scale repulsion
                double repulsionMag = (SAFE_DISTANCE - distToObs) / SAFE_DISTANCE;
                if (distToObs > 0) {
                    repulsion.x /= distToObs;
                    repulsion.y /= distToObs;
                }
                
                // Add repulsion to velocity
                adjustedVelocity.x += repulsion.x * repulsionMag * MAX_SPEED;
                adjustedVelocity.y += repulsion.y * repulsionMag * MAX_SPEED;
            }
        }
        
        // Limit the adjusted velocity
        double speed = sqrt(pow(adjustedVelocity.x, 2) + pow(adjustedVelocity.y, 2));
        if (speed > MAX_SPEED) {
            adjustedVelocity.x = adjustedVelocity.x / speed * MAX_SPEED;
            adjustedVelocity.y = adjustedVelocity.y / speed * MAX_SPEED;
        }
        
        return adjustedVelocity;
    }
    
    // Main navigation function
    Point getNavigationCommand() {
        Point currentPos = positionSensor.getCurrentPosition();
        Point desiredVelocity = calculateVelocityCommand(currentPos);
        return avoidObstacles(currentPos, desiredVelocity);
    }
    
    bool hasArrived() {
        Point currentPos = positionSensor.getCurrentPosition();
        return currentPos.distanceTo(target) < ARRIVAL_THRESHOLD;
    }
    
    Point getTarget() const { return target; }  // Added getter for target
};

// Vehicle Simulation
class AutonomousVehicle {
private:
    Point position;
    GPSSensor gps;
    LidarSensor lidar;
    NavigationController controller;
    
public:
    AutonomousVehicle(Point startPos, Point target)
        : position(startPos),
          gps(startPos),
          lidar(startPos),
          controller(target, gps, lidar) {}
    
    void updatePosition(Point velocity, double dt) {
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        gps.updateTruePosition(position);
        lidar.updateTruePosition(position);
    }
    
    void runMission() {
        Point target = controller.getTarget();  // Use getter instead of direct access
        cout << "Starting mission to target: (" << target.x 
             << ", " << target.y << ")\n";
        
        double dt = 1.0 / CONTROL_LOOP_HZ;
        int step = 0;
        
        while (!controller.hasArrived()) {
            // Get navigation command
            Point cmd = controller.getNavigationCommand();
            
            // Update vehicle position
            updatePosition(cmd, dt);
            
            // Display status
            if (step % 10 == 0) {  // Don't print every step
                cout << "Step " << step << ": Position (" << position.x 
                     << ", " << position.y << ") Velocity (" << cmd.x 
                     << ", " << cmd.y << ")\n";
                
                auto obstacles = lidar.detectObstacles();
                if (!obstacles.empty()) {
                    cout << "  Detected " << obstacles.size() << " obstacles\n";
                }
            }
            
            // Wait for next control cycle
            this_thread::sleep_for(chrono::milliseconds(static_cast<int>(dt * 1000)));
            step++;
        }
        
        cout << "Mission complete! Arrived at target position.\n";
    }
};

int main() {
    // Set up mission
    Point startPosition(0, 0);
    Point targetBeacon(10, 10);
    
    // Create and run vehicle
    AutonomousVehicle vehicle(startPosition, targetBeacon);
    vehicle.runMission();
    
    return 0;
}