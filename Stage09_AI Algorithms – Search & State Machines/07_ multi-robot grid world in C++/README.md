# 07_Multi-Robot Grid World in C++

## Description

This project simulates multiple robots navigating a 2D grid world with obstacles and collision avoidance. Each robot is assigned a unique start and goal position. Robots use Breadth-First Search (BFS) to plan their paths and move step-by-step toward their goals, avoiding collisions with obstacles and other robots. The simulation visualizes the grid, robots, goals, and obstacles in the terminal using ASCII art.

---

## Features

- 2D grid environment with configurable size
- Multiple robots, each with unique start and goal positions
- Obstacles placed on the grid
- BFS pathfinding for each robot
- Step-by-step simulation with collision avoidance
- ASCII visualization of the grid, robots (`1`, `2`, ...), goals (`G`), and obstacles (`X`)
- Simulation ends when all robots reach their goals or after a maximum number of steps

---

## How to Run

1. **Compile the code:**
   ```bash
   g++ main.cpp -o multi_robot_grid -std=c++17
   ```

2. **Run the simulation:**
   ```bash
   ./multi_robot_grid
   ```
   or on Windows:
   ```powershell
   .\multi_robot_grid.exe
   ```

3. **Watch the output:**  
   The terminal will display the grid at each step, showing the robots' positions, their movement, and when they reach their goals.

---

## Example Output

```
. . . . . . . . 
. . . . . . . . 
. . . X . . . . 
. . . X . . . . 
1 . . . . . . . 
. . . . . . . 2 

Step: 0
...
Simulation Complete.
```

---

## Learning Objectives

- Understand multi-agent pathfinding and collision avoidance
- Implement BFS for grid-based navigation
- Practice representing and updating a 2D environment in C++
- Visualize multi-robot movement and interaction in the terminal

---

This project provides a practical introduction to multi-robot coordination, pathfinding, and simulation in C++.