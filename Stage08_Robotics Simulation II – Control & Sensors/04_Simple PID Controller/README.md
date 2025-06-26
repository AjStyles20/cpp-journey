# Simple PID Controller

## Description

This project simulates a simple PID (Proportional-Integral-Derivative) controller applied to a wheel speed control problem. The simulation demonstrates how a PID controller can be used to reach and maintain a target speed in the presence of inertia, friction, and random disturbances. The output is displayed in real time in the console, showing the system's response to the control input.

---

## Features

- Implements a configurable PID controller with anti-windup protection
- Simulates a wheel with inertia, friction, and random noise/disturbances
- Real-time console output of time, speed, error, and control output
- Easy to tune PID parameters and simulation settings

---

## How to Run

1. **Compile the code:**
   ```bash
   g++ main.cpp -o simple_pid_controller -std=c++11
   ```

2. **Run the simulation:**
   ```bash
   ./simple_pid_controller
   ```
   or on Windows:
   ```powershell
   .\simple_pid_controller.exe
   ```

3. **Observe the output:**  
   The console will display the time, current speed, error, and PID output at each time step.

---

## Example Output

```
PID Controller Simulation (Ctrl+C to exit)
Setpoint: 5 rad/s
Time(s)  Speed(rad/s)  Error  Output
 0.000      0.000   5.000  10.000
 0.020      2.000   3.000   7.000
 0.040      3.200   1.800   4.800
 ...
```

---

## Learning Objectives

- Understand the principles of PID control
- See the effect of tuning P, I, and D gains on system response
- Simulate real-world effects like inertia, friction, and noise
- Practice implementing feedback control in C++

---

This project provides a practical introduction to PID control and real-time simulation in C++.