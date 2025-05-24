# 06_MotorControlSystem

## Project Description
This project demonstrates a `Motor` class simulation in C++ that models basic motor operations including start/stop control, speed adjustment, and timed operation. The implementation showcases class encapsulation, state management, and simple time-based simulation.

## Learning Objectives
- Implement class encapsulation with private state variables
- Create methods for device control (start/stop/speed)
- Practice input validation in setter methods
- Simulate real-world operation with time delays
- Understand basic multithreading concepts with `<chrono>`

## Technologies Used
- **C++11** (or later)
- **<chrono>** library for time operations
- **<thread>** for sleep functionality
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Code Runner extension

## How to Run
1. Compile the program:
   ```bash
   g++ main.cpp -o MotorControl
   ```
2. Run the executable:
   ```bash
   ./MotorControl    # Linux/Mac
   .\MotorControl.exe # Windows
   ```

## How to Use
1. The program demonstrates:
   - Motor initialization with custom name
   - State checking with `status()`
   - Start/stop functionality
   - Speed adjustment (0-100%)
   - Timed operation simulation
2. No user input required - demonstration sequence runs automatically

## Example Output
```
=== IndustrialMotor Status ===
State: STOPPED
Speed: 0%

IndustrialMotor started.
IndustrialMotor speed set to 75%
Running IndustrialMotor at 75% for 3 seconds...
[1s] IndustrialMotor humming at 75%...
[2s] IndustrialMotor humming at 75%...
[3s] IndustrialMotor humming at 75%...
IndustrialMotor stopped.

=== IndustrialMotor Status ===
State: STOPPED
Speed: 0%
```

## Key Concepts Demonstrated
- Class encapsulation with private members
- State management (isRunning flag)
- Input validation in `setSpeed()`
- Time-based simulation with `<chrono>`
- Const-correct member functions (`status()`)
- Self-documenting console output

## Class Interface

class Motor {
private:
    int speed;          // 0-100% speed
    bool isRunning;     // On/Off state
    std::string name;   // Identifier
    
public:
    Motor(std::string name = "Motor1");
    void start();
    void stop();
    void setSpeed(int newSpeed);
    void status() const;
    void runForSeconds(int seconds);
};
```

## Notes
- The motor maintains internal state (speed/running status)
- All operations include validation and feedback
- Time simulation uses blocking sleep (for demonstration)
- Can be extended with:
  - RPM calculation based on speed %
  - Overload protection simulation
  - Asynchronous operation
  - Multiple motor coordination
  - Hardware interface for real-world control
