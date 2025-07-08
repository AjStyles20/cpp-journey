# 02_Finite State Robot

## Description

This project demonstrates a simple autonomous robot using a Finite State Machine (FSM) to navigate a 2D grid world. The robot can explore, seek a goal, and recharge at a charging station, switching behaviors based on its battery level and environment. The simulation showcases state transitions, pathfinding, and basic AI decision-making.

---

## Features

- 2D grid world with randomly placed goal and central charging station
- Robot with three states: Explore, SeekGoal, and Recharge
- Finite State Machine (FSM) for state management and transitions
- Random exploration and probabilistic goal discovery
- Simple pathfinding (BFS) to goal or charging station
- Battery management: drains on movement, recharges at station
- Console visualization of the robot, goal, and charging station

---

## How to Run

1. **Compile the code:**
   ```bash
   g++ main.cpp -o finite_state_robot -std=c++11
   ```

2. **Run the program:**
   ```bash
   ./finite_state_robot
   ```
   or on Windows:
   ```powershell
   .\finite_state_robot.exe
   ```

---

## Example Output

```
Step 0: Exploring... (Battery: 100%)
. . . . . . . . . .
. R . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . C . . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . G .

...

Found the goal while exploring!
State change: Explore -> SeekGoal
Seeking goal... (Battery: 98.5%)
...
Goal reached!
Mission accomplished!
```

---

## Learning Objectives

- Understand and implement a Finite State Machine (FSM) for AI behavior
- Practice state transitions and encapsulation in C++
- Apply simple pathfinding and battery/resource management
- Visualize agent-based simulation in the console

---

This project provides a practical introduction to FSM-based AI, pathfinding, and simulation in C++.