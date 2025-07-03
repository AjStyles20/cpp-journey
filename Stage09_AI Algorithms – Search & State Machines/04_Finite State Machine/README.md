# 04_Finite State Machine (FSM) Robot Simulation

## Description

This project demonstrates a finite state machine (FSM) controlling a robot's behavior in a simulated environment. The robot can patrol, chase an enemy, recharge its battery, and investigate suspicious activity. State transitions are triggered by events such as spotting an enemy, losing the enemy, low battery, or completing an investigation. The simulation prints state transitions, actions, and event handling in real time.

---

## Features

- Implements an FSM with four states: Patrol, Chase, Recharge, and Investigate
- Each state has its own behavior and handles relevant events
- Random events (enemy spotted, lost, low battery, etc.) drive state transitions
- Battery level and enemy distance are simulated and affect robot behavior
- Console output shows state transitions, actions, and event processing

---

## How to Run

1. **Compile the code:**
   ```bash
   g++ main.cpp -o fsm_robot -std=c++11
   ```

2. **Run the simulation:**
   ```bash
   ./fsm_robot
   ```
   or on Windows:
   ```powershell
   .\fsm_robot.exe
   ```

3. **Observe the output:**  
   The terminal will display the robot's current state, actions, and transitions as the simulation runs.

---

## Example Output

```
===== ROBOT FSM SIMULATION =====
Starting in Patrol state

--- Update 0 ---
Patrolling... Battery: 100%
--- Update 1 ---
Patrolling... Battery: 99.5%
EVENT: Enemy Spotted
Enemy spotted while patrolling!
Transitioning from Patrol to Chase state
Entering Chase state. Engaging target!
Chasing enemy! Distance: 100m. Battery: 98%
...
===== SIMULATION COMPLETE =====
```

---

## Learning Objectives

- Understand and implement finite state machines for robot control
- Model complex behaviors using simple, maintainable state logic
- Practice event-driven programming and state transitions in C++
- Simulate real-world robot scenarios (patrol, chase, recharge, investigate)

---

This project provides a practical introduction to using finite state machines for autonomous robot control and behavior modeling in C++