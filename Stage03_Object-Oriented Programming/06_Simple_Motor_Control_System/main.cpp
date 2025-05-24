#include <iostream>
#include <thread>
#include <chrono>

class Motor {
private:
    int speed;          // 0-100% speed
    bool isRunning;     // On/Off state
    std::string name;   // Motor identifier

public:
    // Constructor
    Motor(std::string motorName = "Motor1") 
        : speed(0), isRunning(false), name(motorName) {}

    // Start the motor
    void start() {
        if (!isRunning) {
            isRunning = true;
            std::cout << name << " started.\n";
        } else {
            std::cout << name << " is already running.\n";
        }
    }

    // Stop the motor
    void stop() {
        if (isRunning) {
            isRunning = false;
            speed = 0;
            std::cout << name << " stopped.\n";
        } else {
            std::cout << name << " is already stopped.\n";
        }
    }

    // Set speed (0-100)
    void setSpeed(int newSpeed) {
        if (newSpeed >= 0 && newSpeed <= 100) {
            speed = newSpeed;
            std::cout << name << " speed set to " << speed << "%\n";
        } else {
            std::cout << "Invalid speed! Must be 0-100.\n";
        }
    }

    // Get current status
    void status() const {
        std::cout << "\n=== " << name << " Status ===\n"
                  << "State: " << (isRunning ? "RUNNING" : "STOPPED") << "\n"
                  << "Speed: " << speed << "%\n\n";
    }

    // Simulate motor operation
    void runForSeconds(int seconds) {
        if (!isRunning) {
            std::cout << "Cannot run - motor is stopped!\n";
            return;
        }

        std::cout << "Running " << name << " at " << speed << "% for " 
                  << seconds << " seconds...\n";
        
        for (int i = 1; i <= seconds; ++i) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "[" << i << "s] " << name << " humming at " 
                      << speed << "%...\n";
        }
    }
};


int main() {
    Motor m1("IndustrialMotor");
    
    m1.status();    // Check initial state
    m1.start();     // Start the motor
    m1.setSpeed(75); // Set speed
    m1.runForSeconds(3); // Simulate operation
    m1.stop();      // Stop the motor
    m1.status();    // Verify stopped state

    return 0;
}