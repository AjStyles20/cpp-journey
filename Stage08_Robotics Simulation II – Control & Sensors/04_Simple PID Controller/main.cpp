#include <iostream>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <thread>
#include <vector>
#include <random>

using namespace std;
using namespace std::chrono;

class PIDController {
private:
    // PID coefficients
    double Kp, Ki, Kd;
    
    // Controller state
    double integral;
    double previousError;
    steady_clock::time_point lastTime;
    
    // Output limits
    double outputMin, outputMax;
    
    // Reset windup protection
    bool antiWindup;
    
public:
    PIDController(double p, double i, double d, double min, double max, bool antiW = true)
        : Kp(p), Ki(i), Kd(d), integral(0), previousError(0),
          outputMin(min), outputMax(max), antiWindup(antiW),
          lastTime(steady_clock::now()) {}
    
    // Reset controller state
    void reset() {
        integral = 0;
        previousError = 0;
        lastTime = steady_clock::now();
    }
    
    // Update controller with new error measurement
    double update(double setpoint, double measurement) {
        // Calculate time step
        auto now = steady_clock::now();
        double dt = duration_cast<duration<double>>(now - lastTime).count();
        lastTime = now;
        
        // Avoid division by zero
        if (dt <= 0) dt = 0.001;
        
        // Calculate error
        double error = setpoint - measurement;
        
        // Proportional term
        double P = Kp * error;
        
        // Integral term with anti-windup
        integral += error * dt;
        if (antiWindup) {
            // Clamp integral term to prevent windup
            double maxIntegral = (outputMax - P) / Ki;
            double minIntegral = (outputMin - P) / Ki;
            integral = max(minIntegral, min(maxIntegral, integral));
        }
        double I = Ki * integral;
        
        // Derivative term (using measurement instead of error for derivative-on-measurement)
        double derivative = -(measurement - previousError) / dt;
        double D = Kd * derivative;
        
        // Store error for next derivative calculation
        previousError = measurement;
        
        // Calculate and constrain output
        double output = P + I + D;
        return max(outputMin, min(outputMax, output));
    }
    
    // Set new PID coefficients
    void tune(double p, double i, double d) {
        Kp = p;
        Ki = i;
        Kd = d;
        reset();
    }
};

class WheelSimulator {
private:
    double speed;            // Current speed (rad/s)
    double inertia;          // System inertia
    double friction;         // Friction coefficient
    std::mt19937 rng;            // Random number generator
    std::normal_distribution<double> dist; // Noise distribution
    double maxTorque;
public:
    WheelSimulator(double in, double fr, double maxT)
        : speed(0), inertia(in), friction(fr), maxTorque(maxT),
          rng(std::random_device{}()), dist(0.0, 1.0) {}
    
    // Update wheel speed based on applied torque
    void update(double torque, double dt) {
        // Add realistic noise and disturbances
        double disturbance = dist(rng) * 0.2 * maxTorque;
        
        // Calculate net torque (clamped to max)
        double netTorque = max(-maxTorque, min(maxTorque, torque + disturbance));
        
        // Calculate acceleration (F=ma)
        double acceleration = (netTorque - friction * speed) / inertia;
        
        // Update speed
        speed += acceleration * dt;
    }
    
    double getSpeed() const { return speed; }
};

int main() {
    // Create PID controller and wheel simulation
    PIDController pid(2.0, 0.5, 0.1, -10.0, 10.0);
    WheelSimulator wheel(0.1, 0.2, 12.0);
    
    // Simulation parameters
    const double setpoint = 5.0;  // Target speed (rad/s)
    const double dt = 0.02;       // Time step (50Hz)
    
    cout << "PID Controller Simulation (Ctrl+C to exit)\n";
    cout << "Setpoint: " << setpoint << " rad/s\n";
    cout << "Time(s)  Speed(rad/s)  Error  Output\n";
    cout << fixed << setprecision(3);
    
    // Main control loop
    for (double t = 0; t < 10.0; t += dt) {
        // Get current speed
        double speed = wheel.getSpeed();
        
        // Update PID controller
        double output = pid.update(setpoint, speed);
        
        // Apply control output to wheel
        wheel.update(output, dt);
        
        // Display current status
        cout << setw(6) << t << "  " 
             << setw(11) << speed << "  "
             << setw(6) << setpoint - speed << "  "
             << setw(6) << output << "\n";
        
        // Real-time pacing (approximate)
        this_thread::sleep_for(milliseconds(static_cast<int>(dt * 1000)));
    }
    
    return 0;
}