# 07_Warehouse Robot ASCII Grid Path Visualizer

## Description

This project simulates a warehouse robot navigating a 2D grid with obstacles to reach a target location. The robot uses Breadth-First Search (BFS) for pathfinding and visualizes its movement step-by-step in the terminal using ASCII art. Obstacles, the robot, and the target are all displayed on the grid, providing a clear view of the robot's navigation process.

---

## Features

- 2D grid environment with configurable size
- Randomly placed obstacles
- Robot (`R`) and target (`T`) positions
- BFS pathfinding to find the shortest path around obstacles
- Real-time ASCII visualization of the robot's movement
- Step-by-step animation as the robot moves along the planned path

---

## How to Run

1. **Compile the code:**
   ```bash
   g++ main.cpp -o warehouse_robot -std=c++11
   ```

2. **Run the simulation:**
   ```bash
   ./warehouse_robot
   ```
   or on Windows:
   ```powershell
   .\warehouse_robot.exe
   ```

3. **Watch the output:**  
   The terminal will display the grid, robot, target, and obstacles. The robot will plan a path and move step-by-step to the target.

---

## Example Output

```
. . . . . . . . . . 
. . X . . . . . . . 
. . . . . . X . . . 
. . . . . . . . . . 
R . . . . . . . T . 

Planning path...
Path found! Moving robot...
[robot moves step-by-step]
Target reached!
```

---

## Learning Objectives

- Understand grid-based pathfinding using BFS
- Practice representing and updating a 2D environment in C++
- Visualize robot navigation and obstacle avoidance in the terminal
- Simulate real-time robot movement with step-by-step animation

---

This project provides a hands-on introduction to robot navigation, pathfinding, and ASCII-based visualization in C++.