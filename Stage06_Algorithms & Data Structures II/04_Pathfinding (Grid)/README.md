# 04_Pathfinding (Grid)

## Project Description
This project demonstrates pathfinding algorithms on a 2D grid in C++. It implements:
- **Depth-First Search (DFS)** for pathfinding
- **Greedy Best-First Search** using Manhattan distance as a heuristic
- Visualization of the grid, obstacles, and found paths

## Learning Objectives
- Understand grid-based pathfinding
- Implement DFS and heuristic-guided search
- Represent obstacles and paths in a 2D grid
- Visualize search results in the console

## Technologies Used
- **C++11** (or later)
- **STL Containers**: `vector`, `stack`, `queue`, `unordered_set`, `unordered_map`, `priority_queue`
- **Visual Studio Code** (with C/C++ extension)

## How to Run
1. Compile the program:
   ```bash
   g++ -std=c++11 main.cpp -o GridPathfinding
   ```
2. Run the executable:
   ```bash
   ./GridPathfinding    # Linux/Mac
   .\GridPathfinding.exe # Windows
   ```

## How It Works

- The program creates a 10x10 grid.
- Obstacles are placed at specific coordinates, blocking certain cells.
- The user-defined start cell is `(0, 0)` and the end cell is `(9, 9)`.
- The program finds a path from start to end using:
  - **DFS** (may not find the shortest path)
  - **Greedy Best-First Search** (uses Manhattan distance to guide the search)
- The grid and the resulting path are displayed in the console.

## Key Functions

- `addObstacle(int x, int y)` — Adds an obstacle at `(x, y)`
- `findPathDFS(Cell start, Cell end)` — Finds a path using DFS
- `findPathGreedy(Cell start, Cell end)` — Finds a path using Greedy Best-First Search
- `displayGridWithPath(const vector<Cell>& path)` — Prints the grid with the path

## Key Concepts
- **Grid Representation**: 2D vector of booleans for obstacles
- **DFS**: Explores as far as possible before backtracking
- **Greedy Best-First Search**: Uses a heuristic to prioritize cells closer to the goal
- **Path Reconstruction**: Uses parent pointers to reconstruct the found path
- **Visualization**: Console output shows obstacles and path

## Notes
- Obstacles and grid size can be changed in `main.cpp`.
- If no path is found, the path will be empty.
- The DFS path is not guaranteed to be the shortest.
