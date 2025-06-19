#include <iostream>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

class VelocityController {
private:
    double Kp;           // Proportional gain
    double currentSpeed; // Current motor speed (RPM)
    double maxSpeed;     // Maximum possible speed
    double inertia;      // System inertia (simulates acceleration)
    
public:
    VelocityController(double kp, double maxSpd, double systemInertia)
        : Kp(kp), currentSpeed(0), maxSpeed(maxSpd), inertia(systemInertia) {}
    
    // Update motor speed based on desired speed (one time step)
    void update(double desiredSpeed, double dt) {
        // Calculate error
        double error = desiredSpeed - currentSpeed;
        
        // Proportional control
        double controlSignal = Kp * error;
        
        // Simulate motor dynamics (simplified)
        double acceleration = controlSignal / inertia;
        currentSpeed += acceleration * dt;
        
        // Enforce speed limits
        currentSpeed = max(-maxSpeed, min(maxSpeed, currentSpeed));
    }
    
    double getCurrentSpeed() const {
        return currentSpeed;
    }
};

void simulateControlLoop() {
    // Controller parameters
    const double Kp = 0.8;          // Proportional gain
    const double maxSpeed = 1000.0; // RPM
    const double inertia = 2.0;     // Simulated system inertia
    
    // Simulation parameters
    const double dt = 0.1;          // Time step (seconds)
    const double duration = 10.0;   // Simulation duration (seconds)
    
    VelocityController controller(Kp, maxSpeed, inertia);
    double desiredSpeed = 500.0;    // Target speed (RPM)
    
    cout << fixed << setprecision(1);
    cout << "Motor Velocity Control Simulation\n";
    cout << "--------------------------------\n";
    cout << "Target speed: " << desiredSpeed << " RPM\n";
    cout << "Time(s)\tDesired\tActual\tError\n";
    
    for (double t = 0; t <= duration; t += dt) {
        // Change target speed at t=3s and t=7s
        if (t >= 7.0) desiredSpeed = -300.0;
        else if (t >= 3.0) desiredSpeed = 800.0;
        
        controller.update(desiredSpeed, dt);
        double actualSpeed = controller.getCurrentSpeed();
        double error = desiredSpeed - actualSpeed;
        
        cout << t << "\t" << desiredSpeed << "\t" << actualSpeed 
             << "\t" << error << "\n";
        
        // Real-time visualization (optional)
        int barWidth = 60;
        int pos = barWidth * (actualSpeed + maxSpeed) / (2 * maxSpeed);
        cout << "[";
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) cout << "=";
            else if (i == pos) cout << ">";
            else cout << " ";
        }
        cout << "] " << actualSpeed << " RPM\r";
        cout.flush();
        
        this_thread::sleep_for(milliseconds(100)); // Real-time pacing
    }
    cout << "\nSimulation complete.\n";
}

int main() {
    simulateControlLoop();
    return 0;
}