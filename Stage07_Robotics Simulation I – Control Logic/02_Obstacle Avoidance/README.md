# Line Follower Robot Simulator

## Project Description
This program simulates a simple line-following robot equipped with three infrared sensors (left, center, right). The robot detects a black line on a white surface and adjusts its motor speeds to follow the line. The simulation includes sensor noise, basic physics, and real-time ASCII visualization.

## How to Use

1. **Compile and run:**
    ```bash
    g++ main.cpp -o line_follower
    ./line_follower
    ```

2. **Observe the simulation:**
    - The robot (`R`) tries to stay centered on the line (`|`)
    - Sensor states (L/C/R) indicate line detection
    - Display updates in real-time

3. **Terminate** with Ctrl+C

## Key Components

- **Sensor Simulation:**
  - Three IR sensors (left, center, right)
  - Simulated sensor noise and random errors
  - Position-based sensor updates

- **Control Logic:**
  - Basic if-else decision making
  - Motor speed adjustments:
     - Center sensor: forward
     - Left sensor: right turn
     - Right sensor: left turn
     - No sensors: search mode

- **Physics Simulation:**
  - Position model based on differential drive
  - Simulated mechanical drift

- **Visualization:**
  - ASCII-based real-time display
  - Robot and line positioning
  - Sensor and motor state indicators

## Example Output
```
Line Follower Robot Simulation (Ctrl+C to exit)
Legend: R=Robot, |=Line center, L/C/R=Sensor states
[                    R               |          ] Sensors:  C 
```

## Learning Points

- **Sensor Processing:**
  - Multi-sensor input handling
  - Noise management
  - Sensor fusion basics

- **Control Systems:**
  - Proportional control
  - Feedback loops
  - Motor control algorithms

- **Robotics Concepts:**
  - Sensor-motor coordination
  - Line-following strategies
  - Real-world constraints handling

