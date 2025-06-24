# 02_Sensor Fusion

## Description

This project demonstrates basic sensor fusion techniques by combining data from multiple simulated sensors to produce a more accurate or reliable estimate of an environmental variable (such as position, orientation, or temperature). Sensor fusion is a fundamental concept in robotics, autonomous vehicles, and IoT systems, where data from different sources must be integrated to improve system performance and robustness.

---

## Features

- Simulates readings from multiple sensors (e.g., noisy temperature, position, or distance sensors)
- Implements simple fusion algorithms such as:
  - Averaging (mean)
  - Weighted average
  - Median filter
- Compares raw sensor readings and fused output
- Console output showing sensor values and fusion results step-by-step

---

## How to Run

1. **Compile the code:**
   ```bash
   g++ main.cpp -o sensor_fusion
   ```

2. **Run the program:**
   ```bash
   ./sensor_fusion
   ```
   or on Windows:
   ```powershell
   .\sensor_fusion.exe
   ```

3. **Observe the output:**  
   The console will display simulated sensor readings and the fused estimate for each step.

---

## Example Output

```
Step 1:
  Sensor 1: 24.2
  Sensor 2: 23.9
  Sensor 3: 24.5
  Fused (mean): 24.2
  Fused (median): 24.2

Step 2:
  Sensor 1: 24.3
  Sensor 2: 24.0
  Sensor 3: 24.4
  Fused (mean): 24.23
  Fused (median): 24.3
...
```

---

## Learning Objectives

- Understand the concept and importance of sensor fusion
- Simulate noisy sensor data in C++
- Implement and compare basic fusion algorithms
- Analyze the benefits of combining multiple sensor readings

---

This project provides a practical introduction to sensor fusion, a key technique in robotics, autonomous systems, and data science.