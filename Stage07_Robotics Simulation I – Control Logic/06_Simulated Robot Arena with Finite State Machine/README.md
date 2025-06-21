# Simulated Robot Arena with Finite State Machine

## Description

This project simulates a robot operating in a virtual arena using a finite state machine (FSM) to control its behavior. The robot can perform actions such as exploring, avoiding obstacles, searching for targets, and stopping, with transitions between states triggered by simulated sensor inputs or events. This simulation demonstrates how FSMs can be used to manage complex robot behaviors in a structured and maintainable way.

---

## Features

- Simulated robot movement within a 2D arena
- Finite state machine controls robot behavior (e.g., Idle, Explore, AvoidObstacle, Search, Stop)
- State transitions based on simulated sensor data or user commands
- Console output showing robot state, position, and actions in real time
- Easily extendable with new states and behaviors

---

## How to Run

1. **Compile the code:**
   ```bash
   g++ main.cpp -o simulated_robot_arena_fsm
   ```

2. **Run the simulation:**
   ```bash
   ./simulated_robot_arena_fsm
   ```
   or on Windows:
   ```powershell
   .\simulated_robot_arena_fsm.exe
   ```

3. **Observe the output:**  
   The console will display the robot's current state, position, and actions as it navigates the arena.

---

## Example Output

```
State: Idle | Position: (0, 0)
Command: start
Transitioning to Explore state.

State: Explore | Position: (1, 0)
Obstacle detected! Transitioning to AvoidObstacle state.

State: AvoidObstacle | Position: (1, 1)
Path clear. Transitioning to Explore state.

State: Explore | Position: (2, 1)
Target found! Transitioning to Search state.

State: Search | Position: (2, 2)
Search complete. Transitioning to Stop state.
```

---

## Learning Objectives

- Understand and implement finite state machines for robot control
- Simulate robot movement and sensor input in a virtual environment
- Model complex behaviors using simple, maintainable state logic
- Practice structured programming for robotics applications

---

This project provides a practical introduction to using finite state machines for autonomous robot control in