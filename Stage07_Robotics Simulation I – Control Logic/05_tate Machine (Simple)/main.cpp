#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <random>

using namespace std;

// Robot states
enum class RobotState {
    SEARCH,
    HOME,
    FOUND_TARGET
};

class Robot {
private:
    RobotState currentState;
    bool hasTarget;
    int batteryLevel;
    mt19937 rng; // Random number generator

    // Simulate power consumption
    void consumeBattery(int amount) {
        batteryLevel = max(0, batteryLevel - amount);
        if (batteryLevel == 0) {
            cout << "⚠️ Battery depleted! Returning home...\n";
            currentState = RobotState::HOME;
        }
    }

public:
    Robot() : currentState(RobotState::SEARCH), hasTarget(false), batteryLevel(100) {
        rng.seed(random_device()());
    }

    // Update robot state based on current conditions
    void update() {
        // Common battery consumption
        consumeBattery(1);

        // State-specific behavior
        switch (currentState) {
            case RobotState::SEARCH:
                cout << "[SEARCH] Looking for target... ";
                // 20% chance to find target each step
                if (uniform_int_distribution<int>(1, 5)(rng) == 1) {
                    hasTarget = true;
                    currentState = RobotState::FOUND_TARGET;
                    cout << "Target found!\n";
                } else {
                    cout << "No target yet.\n";
                }
                break;

            case RobotState::FOUND_TARGET:
                cout << "[FOUND] Bringing target home...\n";
                // Simulate homing behavior
                if (uniform_int_distribution<int>(1, 3)(rng) == 1) {
                    hasTarget = false;
                    currentState = RobotState::HOME;
                }
                break;

            case RobotState::HOME:
                cout << "[HOME] Recharging battery...\n";
                batteryLevel = min(100, batteryLevel + 10);
                if (batteryLevel == 100) {
                    currentState = RobotState::SEARCH;
                    cout << "Battery charged. Resuming search.\n";
                }
                break;
        }
    }

    // Display current status
    void displayStatus() const {
        cout << "\n=== Robot Status ===\n";
        cout << "State: ";
        switch (currentState) {
            case RobotState::SEARCH: cout << "SEARCHING"; break;
            case RobotState::HOME: cout << "HOMING"; break;
            case RobotState::FOUND_TARGET: cout << "RETURNING WITH TARGET"; break;
        }
        cout << "\nBattery: " << batteryLevel << "%\n";
        cout << "Has Target: " << (hasTarget ? "Yes" : "No") << "\n\n";
    }
};

int main() {
    Robot robot;
    cout << "Robot State Machine Simulation (Ctrl+C to exit)\n";

    // Main simulation loop
    while (true) {
        robot.displayStatus();
        robot.update();
        this_thread::sleep_for(chrono::seconds(1)); // 1 second per step
    }

    return 0;
}