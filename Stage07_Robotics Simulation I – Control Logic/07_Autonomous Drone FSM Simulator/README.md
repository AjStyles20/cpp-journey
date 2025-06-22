# 07_Autonomous Drone FSM Simulator

## Description

This project simulates an autonomous drone using a Finite State Machine (FSM) to manage its behavior. The drone operates in a virtual environment and transitions between states such as Takeoff, Hover, Navigate, AvoidObstacle, Land, and Emergency based on simulated sensor inputs and mission events. This simulator demonstrates how FSMs can be used to control complex autonomous systems in a structured and maintainable way.

---

## Features

- Simulates drone flight with multiple operational states:
  - **Idle**: Waiting for mission start
  - **Takeoff**: Ascending to a safe altitude
  - **Hover**: Maintaining position
  - **Navigate**: Moving toward waypoints
  - **AvoidObstacle**: Reacting to simulated obstacles
  - **Land**: Descending and landing
  - **Emergency**: Handling critical failures
- State transitions triggered by simulated sensor data, user commands, or mission events
- Console output showing current state, position, altitude, and actions in real time
- Easily extendable with new states, behaviors, or sensor models

---

## How to Run

1. **Compile the code:**
   ```bash
   g++ main.cpp -o autonomous_drone_fsm_simulator
   ```

2. **Run the simulator:**
   ```bash
   ./autonomous_drone_fsm_simulator
   ```
   or on Windows:
   ```powershell
   .\autonomous_drone_fsm_simulator.exe
   ```

3. **Observe the output:**  
   The console will display the drone's current state, position, altitude, and actions as it executes its mission.

---

## Example Output

```
State: Idle | Position: (0, 0, 0)
Command: start
Transitioning to Takeoff state.

State: Takeoff | Position: (0, 0, 2)
Reached target altitude. Transitioning to Hover state.

State: Hover | Position: (0, 0, 5)
Waypoint received. Transitioning to Navigate state.

State: Navigate | Position: (10, 5, 5)
Obstacle detected! Transitioning to AvoidObstacle state.

State: AvoidObstacle | Position: (10, 7, 5)
Obstacle cleared. Transitioning to Navigate state.

State: Land | Position: (10, 7, 0)
Landed successfully. Transitioning to Idle state.
```

---

## Learning Objectives

- Understand and implement finite state machines for autonomous drone control
- Simulate drone flight and sensor input in a virtual environment
- Model complex behaviors using simple, maintainable state logic
- Practice structured programming for robotics and UAV applications

---

This project provides a practical introduction to using finite state machines for autonomous