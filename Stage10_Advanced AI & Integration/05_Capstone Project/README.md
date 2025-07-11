# 05_Capstone Project: Finite State Autonomous Robot with Pathfinding

## Description

This project is a capstone demonstration of an autonomous robot navigating a 2D grid world using a finite state machine (FSM) and A* pathfinding. The robot explores the environment, seeks a randomly placed goal, and manages its battery by recharging at a charging station. The simulation integrates exploration, goal-seeking, resource management, and obstacle avoidance.

---

## Features

- 2D grid world with random obstacles, goal, and charging station
- Robot with three states: Explore, SeekGoal, Recharge
- Finite State Machine (FSM) for behavior switching
- A* pathfinding for efficient navigation around obstacles
- Battery management: drains on movement, recharges at station
- Console visualization of the robot’s progress and environment
- Robust handling of blocked paths and replanning

---

## How to Run

1. **Compile the code:**
   ```bash
   g++ main.cpp -o capstone_robot -std=c++11
   ```

2. **Run the program:**
   ```bash
   ./capstone_robot
   ```
   or on Windows:
   ```powershell
   .\capstone_robot.exe
   ```

---

## Example Output

```
Step 0: Exploring... (Battery: 100%)
. . . . . . . . . . . . . . . . . . . . 
. R . . # . . . . . . . . . . . . . . . 
...
Battery low, seeking charging station...
State change: Explore -> Recharge
Moving to charging station... (Battery: 19.5%)
Charging... (Battery: 21.5%)
...
Found the goal while exploring!
State change: Explore -> SeekGoal
Seeking goal... (Battery: 98.5%)
Goal reached!
Mission accomplished!
```

---

## Learning Objectives

- Integrate FSM-based AI and pathfinding in C++
- Practice resource management and state transitions
- Implement robust navigation with obstacle avoidance
- Visualize agent-based simulation and debugging output

---

This capstone project brings together advanced AI, pathfinding, and simulation techniques for autonomous robotics in C++.