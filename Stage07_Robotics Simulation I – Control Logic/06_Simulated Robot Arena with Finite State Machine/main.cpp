#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <iomanip>
#include <unordered_map>

using namespace std;

// Sensor types
struct SensorReadings {
    bool bumpLeft;
    bool bumpRight;
    double lightLevel;  // 0.0 (dark) to 1.0 (bright)
    double irLeft;
    double irRight;
};

// Robot states
enum class RobotState {
    EXPLORE,
    AVOID_OBSTACLE,
    FOLLOW_LIGHT,
    CHARGE_BATTERY
};

class ArenaRobot {
private:
    // Position and orientation
    double x, y;
    double heading;  // radians (0 = right, π/2 = up)
    
    // Energy system
    double battery;
    const double BATTERY_DRAIN = 0.5;
    const double BATTERY_MAX = 100.0;
    
    // State machine
    RobotState currentState;
    unordered_map<RobotState, string> stateNames = {
        {RobotState::EXPLORE, "EXPLORE"},
        {RobotState::AVOID_OBSTACLE, "AVOID"},
        {RobotState::FOLLOW_LIGHT, "FOLLOW LIGHT"},
        {RobotState::CHARGE_BATTERY, "CHARGING"}
    };
    
    // Random number generation
    mt19937 rng;
    uniform_real_distribution<double> dist;
    
    // Movement parameters
    const double MOVE_SPEED = 0.2;
    const double TURN_SPEED = 0.3;
    
public:
    ArenaRobot(double startX, double startY) : 
        x(startX), y(startY), heading(0), battery(BATTERY_MAX),
        currentState(RobotState::EXPLORE),
        rng(random_device()()), dist(0.0, 1.0) {}
    
    // Simulate sensor readings based on environment
    SensorReadings readSensors() {
        SensorReadings readings;
        
        // Simulate bump sensors (10% chance of hitting something)
        readings.bumpLeft = dist(rng) < 0.1;
        readings.bumpRight = dist(rng) < 0.1;
        
        // Simulate light gradient (brighter toward center)
        double centerDist = sqrt(x*x + y*y);
        readings.lightLevel = max(0.0, 1.0 - centerDist/5.0);
        
        // Simulate IR sensors (closer to walls = higher values)
        readings.irLeft = min(1.0, max(0.0, (4.0 - (y + 4.0)) / 4.0));
        readings.irRight = min(1.0, max(0.0, (4.0 - (4.0 - y)) / 4.0));
        
        return readings;
    }
    
    // Update robot state and position
    void update() {
        // Drain battery
        battery = max(0.0, battery - BATTERY_DRAIN);
        
        // Get sensor data
        SensorReadings sensors = readSensors();
        
        // State transitions (higher priority states first)
        if (battery < 20.0) {
            currentState = RobotState::CHARGE_BATTERY;
        } 
        else if (sensors.bumpLeft || sensors.bumpRight) {
            currentState = RobotState::AVOID_OBSTACLE;
        }
        else if (sensors.lightLevel > 0.7) {
            currentState = RobotState::FOLLOW_LIGHT;
        }
        else if (battery > 30.0) {
            currentState = RobotState::EXPLORE;
        }
        
        // State behaviors
        switch (currentState) {
            case RobotState::EXPLORE: {
                // Random exploration
                if (dist(rng) < 0.2) {
                    heading += (dist(rng) - 0.5) * TURN_SPEED;
                }
                x += MOVE_SPEED * cos(heading);
                y += MOVE_SPEED * sin(heading);
                break;
            }
                
            case RobotState::AVOID_OBSTACLE: {
                // Back up and turn away from obstacle
                x -= MOVE_SPEED * 0.5 * cos(heading);
                y -= MOVE_SPEED * 0.5 * sin(heading);
                heading += sensors.bumpLeft ? -TURN_SPEED : TURN_SPEED;
                break;
            }
                
            case RobotState::FOLLOW_LIGHT: {
                // Move toward light source (center)
                double targetAngle = atan2(-y, -x);
                double angleDiff = fmod(targetAngle - heading + M_PI, 2*M_PI) - M_PI;
                heading += angleDiff * 0.1;
                x += MOVE_SPEED * cos(heading);
                y += MOVE_SPEED * sin(heading);
                break;
            }
                
            case RobotState::CHARGE_BATTERY: {
                // Simulate charging at edge of arena
                if (x < -3.5 || x > 3.5 || y < -3.5 || y > 3.5) {
                    battery = min(BATTERY_MAX, battery + 2.0);
                } else {
                    // Move toward nearest edge
                    double edgeX = (abs(x) > abs(y)) ? (x > 0 ? 4.0 : -4.0) : x;
                    double edgeY = (abs(y) > abs(x)) ? (y > 0 ? 4.0 : -4.0) : y;
                    double targetAngle = atan2(edgeY - y, edgeX - x);
                    double angleDiff = fmod(targetAngle - heading + M_PI, 2*M_PI) - M_PI;
                    heading += angleDiff * 0.2;
                    x += MOVE_SPEED * 0.7 * cos(heading);
                    y += MOVE_SPEED * 0.7 * sin(heading);
                }
                break;
            }
        }
        
        // Keep robot within arena bounds (5x5 units)
        x = max(-4.0, min(4.0, x));
        y = max(-4.0, min(4.0, y));
    }
    
    // Display robot status and simple arena view
    void display() const {
        const int size = 21;  // ASCII display size
        const double scale = size / 8.0;
        
        cout << "\033[2J\033[1;1H";  // Clear screen
        
        // Header with status info
        cout << "Robot Arena Simulation (Ctrl+C to exit)\n";
        cout << "State: " << stateNames.at(currentState) 
             << " | Battery: " << int(battery) << "%\n";
        cout << "Position: (" << fixed << setprecision(1) << x << ", " << y << ")\n\n";
        
        // Simple arena visualization
        for (int i = 0; i < size; i++) {
            double arenaY = 4.0 - (i / scale);
            for (int j = 0; j < size; j++) {
                double arenaX = -4.0 + (j / scale);
                
                // Check if this cell contains the robot
                if (abs(arenaX - x) < 0.3 && abs(arenaY - y) < 0.3) {
                    // Show robot direction
                    char dir;
                    double angle = fmod(heading + M_PI/4, 2*M_PI);
                    if (angle < M_PI/2) dir = '>';
                    else if (angle < M_PI) dir = '^';
                    else if (angle < 3*M_PI/2) dir = '<';
                    else dir = 'v';
                    cout << dir;
                } 
                // Check if near center (light source)
                else if (sqrt(arenaX*arenaX + arenaY*arenaY) < 1.0) {
                    cout << "*";
                }
                // Check if near edge (charging station)
                else if (abs(arenaX) > 3.5 || abs(arenaY) > 3.5) {
                    cout << "#";
                }
                else {
                    cout << ".";
                }
                cout << " ";
            }
            cout << "\n";
        }
        
        // Sensor display
        SensorReadings sensors = const_cast<ArenaRobot*>(this)->readSensors();
        cout << "\nSensors: ";
        cout << "Bump[" << (sensors.bumpLeft ? "L" : " ") << (sensors.bumpRight ? "R" : " ") << "] ";
        cout << "Light:" << fixed << setprecision(2) << sensors.lightLevel << " ";
        cout << "IR[" << sensors.irLeft << "," << sensors.irRight << "]\n";
    }
};

int main() {
    ArenaRobot robot(0.0, 0.0);
    
    cout << "Robot Arena Simulation\n";
    cout << "Starting simulation...\n";
    this_thread::sleep_for(chrono::seconds(1));
    
    // Main simulation loop
    while (true) {
        robot.update();
        robot.display();
        this_thread::sleep_for(chrono::milliseconds(200)); // 5 FPS
    }
    
    return 0;
}