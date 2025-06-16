# 01_Line Follower Robot Simulator

## Project Description
This program simulates a basic line-following robot equipped with three infrared sensors (left, center, right). The robot detects a black line on a white surface and adjusts its motor speeds to follow the line. The simulation includes sensor noise, simple physics, and real-time ASCII visualization.

---

## How to Use

1. **Compile and run:**
   ```bash
   g++ main.cpp -o line_follower
   ./line_follower
   ```

2. **Observe the simulation:**
   - The robot (`R`) tries to stay centered on the line (`|`).
   - Sensor states (L/C/R) show which sensors detect the line.
   - The display updates in real-time.

3. **Terminate** with Ctrl+C.

---

## Key Components

- **Sensor Simulation:**  
  - 3 IR sensors (left, center, right)
  - Simulates sensor noise with random errors
  - Updates based on robot's position relative to the line

- **Control Logic:**  
  - Basic if-else decision making
  - Adjusts motor speeds to follow the line:
    - Center sensor: go straight
    - Left sensor: turn right
    - Right sensor: turn left
    - No sensors: search pattern

- **Physics Simulation:**  
  - Simple position model based on wheel speed difference
  - Simulates mechanical drift with randomness

- **Visualization:**  
  - Real-time ASCII display
  - Shows robot position relative to the line
  - Displays sensor states and motor behavior

---

## Example Output

```
Line Follower Robot Simulation (Ctrl+C to exit)
Legend: R=Robot, |=Line center, L/C/R=Sensor states
[                    R               |          ] Sensors:  C 
```

---

## Learning Points

- **Sensor Processing:**  
  - Reading multiple binary sensors
  - Handling sensor noise/errors
  - Making decisions based on sensor combinations

- **Control Systems:**  
  - Proportional response to error (position offset)
  - Basic feedback loop implementation
  - Simple motor mixing algorithm

- **Robotics Concepts:**  
  - Sensor-motor coordination
  - Line-following algorithms
  - Dealing with real-world imperfections

---

This simulation provides a foundation for understanding basic robotic control systems and demonstrates how simple conditional logic can create complex autonomous behavior. 