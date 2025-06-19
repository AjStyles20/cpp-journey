# 04_Velocity Controller

## Description

This project demonstrates a basic velocity controller, a fundamental component in robotics and automation for achieving and maintaining a target speed. The controller compares the desired (target) velocity with the current velocity and computes a control output (such as motor power or PWM signal) to minimize the difference. Control strategies include proportional (P), proportional-integral (PI), and proportional-integral-derivative (PID) algorithms.

---

## Features

- Reads target and current velocity values (via user input, file, or simulated sensor)
- Calculates control output to adjust system velocity
- Supports both proportional (P) and PID control logic
- Displays step-by-step velocity and control output for each iteration
- Simulates system response over multiple time steps

---

## How to Run

1. **Compile the code:**
    ```bash
    g++ main.cpp -o velocity_controller
    ```

2. **Run the program:**
    ```bash
    ./velocity_controller
    ```
    On Windows:
    ```powershell
    .\velocity_controller.exe
    ```

3. **Configure parameters as prompted or by editing the code:**
    - Target velocity
    - Initial velocity
    - Controller gains (Kp, Ki, Kd)
    - Number of simulation steps

---

## Example Output

```
Step  Target  Current  Output
  1    1.00    0.00    0.20
  2    1.00    0.20    0.16
  3    1.00    0.36    0.13
  ...
 10    1.00    0.85    0.03
```

---

## Learning Objectives

- Grasp feedback control concepts (P, PI, PID)
- Implement a simple velocity controller in C++
- Simulate and observe system response to control actions
- Practice tuning controller parameters for optimal performance

---

This project serves as an introduction to feedback control systems in robotics and provides a practical foundation for further exploration.
