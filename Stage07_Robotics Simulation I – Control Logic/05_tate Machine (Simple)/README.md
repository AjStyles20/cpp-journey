# State Machine (Simple)

## Description

This project demonstrates a simple state machine implementation in C++. A state machine is a programming pattern used to model systems that transition between a finite number of states based on events or conditions. State machines are widely used in robotics, games, embedded systems, and process control.

---

## Features

- Defines a set of states (e.g., Idle, Moving, Error)
- Transitions between states based on user input or simulated events
- Prints the current state and transitions in real time
- Easy to extend with new states and transitions

---

## How to Run

1. **Compile the code:**
   ```bash
   g++ main.cpp -o state_machine_simple
   ```

2. **Run the program:**
   ```bash
   ./state_machine_simple
   ```
   or on Windows:
   ```powershell
   .\state_machine_simple.exe
   ```

3. **Follow the on-screen prompts** to trigger state transitions.

---

## Example Output

```
Current State: Idle
Enter command (start/stop/error/reset): start
Transitioning to Moving state.

Current State: Moving
Enter command (start/stop/error/reset): error
Transitioning to Error state.

Current State: Error
Enter command (start/stop/error/reset): reset
Transitioning to Idle state.
```

---

## Learning Objectives

- Understand the concept of finite state machines (FSM)
- Implement state transitions and event handling in C++
- Model simple system behavior using states

---


This project provides a foundation for modeling and controlling system behavior using state machines in C