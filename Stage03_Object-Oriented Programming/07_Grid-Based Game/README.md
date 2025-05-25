# 07_Grid-Based Game

## Project Description
This project demonstrates inheritance and polymorphism in C++ through a simple grid-based game featuring a player-controlled character and chasing enemy. The implementation showcases virtual functions, derived class behavior, and basic game loop mechanics.

## Learning Objectives
- Implement inheritance with base and derived classes
- Understand virtual functions and polymorphism
- Create interactive game mechanics
- Handle user input for character control
- Develop simple AI behavior for enemies

## Technologies Used
- **C++11** (or later)
- **Virtual functions** for polymorphic behavior
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Code Runner extension

## How to Run
1. Compile the program:
   ```bash
   g++ main.cpp -o GridGame
   ```
2. Run the executable:
   ```bash
   ./GridGame    # Linux/Mac
   .\GridGame.exe # Windows
   ```

## How to Use
1. Controls:
   - W: Move up
   - A: Move left
   - S: Move down
   - D: Move right
   - Q: Quit game
2. The enemy will automatically chase the player
3. Game ends when enemy catches player or player quits

## Example Output
```
Player Position: (0, 0)
Enemy Position: (5, 5)
Enter move: d
Player Position: (1, 0)
Enemy Position: (4, 5)
Enter move: w
Player Position: (1, -1)
Enemy Position: (3, 4)
...
Game Over! Enemy caught the player!
```

## Key Concepts Demonstrated
- Inheritance (`Entity` base class)
- Polymorphic movement behavior
- Player input handling
- Enemy chasing AI
- Collision detection
- Game loop implementation

## Class Hierarchy
```
Entity (base)
├── move() (virtual)
├── getX(), getY()
│
├── Player (derived)
│   └── handleInput() (WASD controls)
│
└── Enemy (derived)
    └── chase() (simple AI)
```

## Notes
- The `Entity` class provides base movement functionality
- `Player` implements direction-based movement
- `Enemy` implements simple chasing behavior

