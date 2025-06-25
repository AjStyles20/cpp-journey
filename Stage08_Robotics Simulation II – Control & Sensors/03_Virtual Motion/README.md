# 03_Virtual Motion Simulator

## Description

This project simulates the motion of a robot along a straight track using basic physics and control logic. The robot accelerates, decelerates, and stops at a specified target position, respecting physical constraints such as maximum speed and acceleration. The simulation provides real-time ASCII visualization of the robot's position, velocity, acceleration, and progress toward the target.

---

## Features

- Simulates 1D robot motion with acceleration, deceleration, and speed limits
- Sets a target position for the robot to reach
- Automatically handles acceleration and braking phases
- Real-time console visualization of the robot's position on a track
- Displays current time, position, velocity, and acceleration
- Includes a simple distance-time graph for additional insight

---

## How to Run

1. **Compile the code:**
   ```bash
   g++ main.cpp -o virtual_motion -std=c++11
   ```

2. **Run the simulation:**
   ```bash
   ./virtual_motion
   ```
   or on Windows:
   ```powershell
   .\virtual_motion.exe
   ```

3. **Observe the output:**  
   The console will update in real time, showing the robot's progress toward the target.

4. **Stop the simulation:**  
   Press `Ctrl+C` to exit.

---

## Example Output

```
Robot Motion Physics Simulation
Setting target position to 10 meters...
Robot Motion Simulator (Ctrl+C to exit)
Target: 10.00m
Time:  0.10s  Pos:  0.05m  Vel:  0.50m/s  Accel:  1.00m/s²
|R-------------------------------------------------|
...
Distance-Time Graph:
 10.0m  |
  9.0m  |
  8.0m  |
  7.0m  |
  6.0m  |
  5.0m  |
  4.0m  |
  3.0m  |
  2.0m  |
  1.0m  R
  0.0m  |
```

---

## Learning Objectives

- Understand basic kinematics and motion control in robotics
- Implement acceleration, deceleration, and speed limiting in C++
- Visualize real-time simulation data in the terminal
- Practice feedback control for reaching a target position

---

This project provides a hands-on introduction to simulating and visualizing robot motion using C++ and basic physics principles. 