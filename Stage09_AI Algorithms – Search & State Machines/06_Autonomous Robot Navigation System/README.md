# 06_Autonomous Robot Navigation System

## Description

This project simulates an autonomous robot navigating a 2D grid map from a start position to a goal using the A* pathfinding algorithm. The robot moves step-by-step, adjusting its orientation and following the computed path, while the simulation visualizes the robot, its path, and the environment in the terminal using ASCII art.

---

## Features

- 2D grid map with walls (`#`), open spaces (`.`), start (`S`), and goal (`G`)
- Robot visualized with orientation (`^`, `>`, `v`, `<`)
- A* pathfinding for optimal route planning
- Step-by-step movement and orientation adjustment
- ASCII visualization of the map, robot, and path at each step
- Real-time simulation with adjustable control loop speed

---

## How to Run

1. **Compile the code:**
   ```bash
   g++ main.cpp -o autonomous_robot_nav -std=c++11
   ```

2. **Run the simulation:**
   ```bash
   ./autonomous_robot_nav
   ```
   or on Windows:
   ```powershell
   .\autonomous_robot_nav.exe
   ```

3. **Observe the output:**  
   The terminal will display the map at each step, showing the robot's position, orientation, and the planned path.

---

## Example Output

```
Step 0:

####################
#S....#...........#
#.###.#.#####.###.#
#.#...#.....#.....#
#.#.#####.#.###.#.#
#.#.......#.......#
#.#######.#.#####.#
#...............G.#
####################

Step 1:
...
Robot reached the goal!
Final position:
...
```

---

## Learning Objectives

- Understand and implement A* pathfinding in grid environments
- Simulate robot movement and orientation in discrete steps
- Visualize robot navigation and path planning in the terminal
- Practice structured programming for robotics and AI

---

This project provides a practical introduction to autonomous navigation, pathfinding, and real-time simulation in C++.