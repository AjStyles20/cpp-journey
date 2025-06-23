# 01_Grid Navigation Robot Simulator

## Description

This project simulates a robot navigating a 2D grid environment. The robot can move in four directions (up, down, left, right) and is tasked with reaching a specified goal position while avoiding obstacles. The simulator demonstrates basic pathfinding, movement logic, and grid-based world representation, providing a foundation for more advanced robotics and AI navigation algorithms.

---

## Features

- 2D grid environment with customizable size
- Robot can move in four cardinal directions
- Obstacles can be placed on the grid
- Start and goal positions are configurable
- Simple pathfinding (e.g., greedy, BFS, or manual step-by-step)
- Console visualization of the grid, robot, obstacles, and goal
- Step-by-step or automatic navigation modes

---

## How to Run

1. **Compile the code:**
   ```bash
   g++ main.cpp -o grid_navigation_robot
   ```

2. **Run the simulator:**
   ```bash
   ./grid_navigation_robot
   ```
   or on Windows:
   ```powershell
   .\grid_navigation_robot.exe
   ```

3. **Follow the prompts** to set grid size, place obstacles, and define start/goal positions, or edit the code to use preset values.

---

## Example Output

```
Grid Navigation Robot Simulator
Legend: R=Robot, G=Goal, X=Obstacle, .=Empty

. . . . . . .
. X X . . . .
. . . . X . .
R . X . . . G
. . . . . . .

Step 1: Robot moves right
Step 2: Robot moves right
Step 3: Robot moves down
...
Goal reached in 8 steps!
```

---

## Learning Objectives

- Representing environments as 2D grids in C++
- Implementing basic robot movement and collision checking
- Visualizing robot navigation in the console
- Understanding and applying simple pathfinding strategies

---

This project provides a hands-on introduction to grid-based navigation and pathfinding, essential concepts in robotics and AI.