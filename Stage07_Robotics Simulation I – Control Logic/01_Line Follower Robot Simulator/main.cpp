#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h> // for usleep

using namespace std;

// Simulated line sensor array
class LineSensorArray {
private:
    vector<bool> sensors; // true = line detected
    double position;      // robot's position relative to line (0 = centered)

public:
    LineSensorArray() : sensors(3, false), position(0.0) {
        srand(time(0));
    }

    // Update sensor readings based on robot's position
    void updateSensors() {
        // Clear all sensors
        sensors[0] = sensors[1] = sensors[2] = false;
        
        // Simple line detection model
        if (position < -0.5) {
            sensors[0] = true; // Only left sensor on line
        } else if (position > 0.5) {
            sensors[2] = true; // Only right sensor on line
        } else {
            sensors[1] = true; // Center sensor on line
        }
        
        // Add some randomness to simulate real sensors
        for (size_t i = 0; i < sensors.size(); ++i) {
            if (rand() % 100 < 5) { // 5% chance of sensor error
                sensors[i] = !sensors[i];
            }
        }
    }

    // Get current sensor readings [left, center, right]
    vector<bool> getReadings() const {
        return sensors;
    }

    // Update robot's position based on motor speeds
    void updatePosition(double leftSpeed, double rightSpeed) {
        // Simple physics model - difference in wheel speeds affects position
        double speedDiff = rightSpeed - leftSpeed;
        position += speedDiff * 0.1;
        
        // Add some drift to simulate imperfect movement
        position += (rand() % 100 - 50) * 0.005;
    }

    // Get current position (for display)
    double getPosition() const {
        return position;
    }
};

// Line follower robot controller
class LineFollower {
private:
    double leftSpeed, rightSpeed;
    
public:
    LineFollower() : leftSpeed(0.5), rightSpeed(0.5) {}
    
    // Update motor speeds based on sensor readings
    void update(const vector<bool>& sensors) {
        // Basic line-following logic
        if (sensors[1]) { // Center sensor on line
            leftSpeed = rightSpeed = 0.5; // Go straight
        } 
        else if (sensors[0]) { // Left sensor on line
            leftSpeed = 0.3;    // Turn right
            rightSpeed = 0.7;
        } 
        else if (sensors[2]) { // Right sensor on line
            leftSpeed = 0.7;    // Turn left
            rightSpeed = 0.3;
        } 
        else { // No sensors on line
            // Search pattern - turn right slowly
            leftSpeed = 0.4;
            rightSpeed = 0.2;
        }
    }

    // Get current motor speeds
    pair<double, double> getSpeeds() const {
        return {leftSpeed, rightSpeed};
    }
};

// Visualize the robot and line
void display(const LineSensorArray& sensorArray) {
    const int fieldWidth = 40;
    double pos = sensorArray.getPosition();
    int robotPos = static_cast<int>((pos + 1.0) * (fieldWidth/2));
    robotPos = max(0, min(fieldWidth-1, robotPos));
    
    cout << "\r["; // Carriage return to overwrite line
    for (int i = 0; i < fieldWidth; i++) {
        if (i == robotPos) {
            cout << "R"; // Robot position
        } else if (i == fieldWidth/2) {
            cout << "|"; // Line position
        } else {
            cout << " ";
        }
    }
    cout << "] ";
    
    // Display sensor states
    vector<bool> sensors = sensorArray.getReadings();
    cout << "Sensors: ";
    cout << (sensors[0] ? "L" : " ");
    cout << (sensors[1] ? "C" : " ");
    cout << (sensors[2] ? "R" : " ");
    
    // Display motor speeds
    cout.flush();
}

int main() {
    LineSensorArray sensorArray;
    LineFollower follower;
    
    cout << "Line Follower Robot Simulation (Ctrl+C to exit)\n";
    cout << "Legend: R=Robot, |=Line center, L/C/R=Sensor states\n";
    
    while (true) {
        // Update sensor readings based on current position
        sensorArray.updateSensors();
        vector<bool> sensors = sensorArray.getReadings();
        
        // Get motor control outputs
        follower.update(sensors);
        auto [leftSpeed, rightSpeed] = follower.getSpeeds();
        
        // Update position based on motor speeds
        sensorArray.updatePosition(leftSpeed, rightSpeed);
        
        // Display current state
        display(sensorArray);
        
        // Control simulation speed
        usleep(100000); // 100ms delay
    }
    
    return 0;
}