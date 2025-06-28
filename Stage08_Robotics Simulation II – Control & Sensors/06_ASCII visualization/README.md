# 06_ASCII Visualization Robot Simulator

## Description

This project simulates a robot navigating a 2D grid environment with obstacles and a target beacon, using real-time ASCII art for visualization in the terminal. The robot uses simple navigation and obstacle avoidance logic to reach the beacon, and the simulation displays the robot, obstacles, and beacon on a grid at each step.

---

## Features

- 2D grid environment with configurable obstacles and beacon position
- Robot moves toward the beacon while avoiding obstacles
- Real-time ASCII visualization of the robot (`R`), beacon (`B`), and obstacles (`X`)
- Step-by-step display of robot position, distance to beacon, and navigation progress
- Adjustable simulation speed and grid size

---

## How to Run

1. **Compile the code:**
   ```bash
   g++ main.cpp -o ascii_visualization -std=c++11
   ```

2. **Run the simulation:**
   ```bash
   ./ascii_visualization
   ```
   or on Windows:
   ```powershell
   .\ascii_visualization.exe
   ```

3. **Watch the output:**  
   The terminal will update in real time, showing the robot's progress toward the beacon and its avoidance of obstacles.

4. **Stop the simulation:**  
   Press `Ctrl+C` to exit at any time.

---

## Example Output

```
  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
 0 . . . . . . . . . . . . . . . . . . . .
 1 R . . . . . . . . . . . . . . . . . . .
 2 . . . . . . . . . . . . . . . . . . . .
 3 . . . . . . . . . . . . . . . . . . . .
 4 . . . . . . . . . . . . . . . . . . . .
 5 . . . . . X X X . . . . . . . . . . . .
 6 . . . . . . . . . . . . . . . . . . . .
 7 . . . . . . . . . . . . . . . . . . . .
 8 . . . . . . . . . . . . . . X . . . . .
 9 . . . . . . . . . . . . . . X . . . . .
10 . . . . . . . . . . X X X . X . . . . .
...
Legend: R=Robot, B=Beacon, X=Obstacle

Step: 0
Position: (1.0, 1.0)
Distance to beacon: 19.8
```

---

## Learning Objectives

- Visualize robot navigation and obstacle avoidance in a terminal environment
- Implement simple movement and avoidance logic in C++
- Practice real-time simulation and feedback loops
- Understand how to represent and update a 2D grid world

---

This project provides a hands-on introduction to robotics simulation, visualization, and basic navigation algorithms using C++ and terminal graphics.