# Autonomous Task

## Description

This project simulates an autonomous vehicle tasked with navigating from a start position to a target beacon in a 2D environment. The vehicle uses simulated GPS and Lidar sensors to determine its position and detect obstacles. A navigation controller computes velocity commands to reach the target while avoiding obstacles using simple proportional control and repulsion logic. The simulation outputs the vehicle's progress and obstacle detections in real time.

---

## Features

- Simulated 2D environment with configurable start and target positions
- Virtual GPS sensor with noise for position estimation
- Virtual Lidar sensor for obstacle detection
- Navigation controller for path planning and obstacle avoidance
- Real-time console output of position, velocity, and detected obstacles
- Mission completes automatically when the vehicle reaches the target

---

## How to Run

1. **Compile the code:**
   ```bash
   g++ main.cpp -o autonomous_task -std=c++11
   ```

2. **Run the simulation:**
   ```bash
   ./autonomous_task
   ```
   or on Windows:
   ```powershell
   .\autonomous_task.exe
   ```

3. **Observe the output:**  
   The console will display the vehicle's position, velocity, and any detected obstacles at regular intervals until the mission is complete.

---

## Example Output

```
Starting mission to target: (10, 10)
Step 0: Position (0, 0) Velocity (3.54, 3.54)
Step 10: Position (3.5, 3.5) Velocity (2.24, 2.24)
  Detected 1 obstacles
Step 20: Position (6.2, 6.2) Velocity (1.34, 1.34)
Mission complete! Arrived at target position.
```

---

## Learning Objectives

- Understand basic concepts of autonomous navigation and control
- Simulate sensor fusion using GPS and Lidar data
- Implement simple obstacle avoidance strategies
- Practice real-time simulation and feedback in C++

---

This project provides a practical introduction to autonomous vehicle navigation, sensor integration, and real-time control in a simulated environment.