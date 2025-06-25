#include <iostream>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;
using namespace std::chrono;

class MotionSimulator {
private:
    // Physics parameters
    double position;     // Current position (m)
    double velocity;     // Current velocity (m/s)
    double acceleration; // Current acceleration (m/s²)
    
    // Physical limits
    const double MAX_ACCEL = 1.0;   // Maximum acceleration (m/s²)
    const double MAX_DECEL = -2.0;  // Maximum braking deceleration (m/s²)
    const double MAX_SPEED = 5.0;   // Maximum velocity (m/s)
    
    // Control parameters
    double targetSpeed;  // Desired velocity
    double targetPos;    // Desired position
    
    // Time tracking
    steady_clock::time_point startTime;
    double simTime;      // Simulation time (s)
    
public:
    MotionSimulator() : position(0), velocity(0), acceleration(0),
                       targetSpeed(0), targetPos(0), simTime(0) {
        startTime = steady_clock::now();
    }
    
    // Set target position (triggers motion)
    void setTarget(double newTarget) {
        targetPos = newTarget;
        targetSpeed = (newTarget > position) ? MAX_SPEED : -MAX_SPEED;
    }
    
    // Update physics for one time step
    void update(double dt) {
        // Calculate time since start
        simTime = duration_cast<duration<double>>(steady_clock::now() - startTime).count();
        
        // Calculate distance to target
        double distance = targetPos - position;
        double stoppingDistance = (velocity * velocity) / (2 * -MAX_DECEL);
        
        // Determine if we need to start decelerating
        if ((distance > 0 && distance <= stoppingDistance) || 
            (distance < 0 && distance >= -stoppingDistance)) {
            // Begin deceleration phase
            targetSpeed = 0;
        }
        
        // Calculate acceleration needed to reach target speed
        double speedError = targetSpeed - velocity;
        
        if (fabs(speedError) > 0.1) { // Deadband to prevent oscillation
            if (speedError > 0) {
                acceleration = min(MAX_ACCEL, speedError);
            } else {
                acceleration = max(MAX_DECEL, speedError);
            }
        } else {
            acceleration = 0;
        }
        
        // Update velocity and position
        velocity += acceleration * dt;
        
        // Enforce speed limits
        velocity = max(-MAX_SPEED, min(MAX_SPEED, velocity));
        
        // Update position
        position += velocity * dt;
        
        // Stop if very close to target with low velocity
        if (fabs(distance) < 0.01 && fabs(velocity) < 0.1) {
            velocity = 0;
            acceleration = 0;
        }
    }
    
    // Display current status
    void display() const {
        const int trackLength = 50;
        int posMarker = static_cast<int>((position / targetPos) * trackLength);
        posMarker = max(0, min(trackLength, posMarker));
        
        cout << "\033[2J\033[1;1H"; // Clear screen
        cout << "Robot Motion Simulator (Ctrl+C to exit)\n";
        cout << "Target: " << fixed << setprecision(2) << targetPos << "m\n";
        cout << "Time: " << setw(5) << simTime << "s  ";
        cout << "Pos: " << setw(5) << position << "m  ";
        cout << "Vel: " << setw(5) << velocity << "m/s  ";
        cout << "Accel: " << setw(5) << acceleration << "m/s²\n";
        
        cout << "[";
        for (int i = 0; i < trackLength; i++) {
            if (i == posMarker) {
                cout << "R";
            } else if (i == 0) {
                cout << "|";
            } else if (i == trackLength - 1) {
                cout << "|";
            } else {
                cout << "-";
            }
        }
        cout << "]\n";
        
        // Additional visualization
        cout << "\nDistance-Time Graph:\n";
        const int graphHeight = 10;
        int posGraph = static_cast<int>((position / targetPos) * graphHeight);
        posGraph = max(0, min(graphHeight, posGraph));
        
        for (int i = graphHeight; i >= 0; i--) {
            cout << setw(5) << fixed << setprecision(1) << (targetPos * i/graphHeight) << "m ";
            if (i == posGraph) {
                cout << " R\n";
            } else {
                cout << " |\n";
            }
        }
    }
};

int main() {
    MotionSimulator robot;
    
    cout << "Robot Motion Physics Simulation\n";
    cout << "Setting target position to 10 meters...\n";
    robot.setTarget(10.0);
    
    // Main simulation loop
    while (true) {
        robot.update(0.1); // 100ms time step
        robot.display();
        this_thread::sleep_for(milliseconds(100)); // Real-time pacing
    }
    
    return 0;
}