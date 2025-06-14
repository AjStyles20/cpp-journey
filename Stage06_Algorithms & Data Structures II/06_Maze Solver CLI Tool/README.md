# 06_Maze Solver CLI Tool

## Project Description
A command-line tool that solves mazes using Breadth-First Search (BFS) or A* (A-star) algorithms. The maze is read from a text file, and the solution path is displayed in the terminal.

## Features
- Supports BFS (default) and A* algorithms for pathfinding.
- Prints the maze with the solution path marked.
- Reports the number of steps and time taken to solve.
- Handles invalid mazes and missing start/end points.

## Maze File Format
- Maze is a plain text file.
- Characters:
  - `#` = Wall
  - `.` = Open path
  - `S` = Start
  - `E` = End

**Example:**
```
#######
#S...E#
#.###.#
#.....#
#######
```


## How to Run
1. Compile the program:
   ```bash
   g++ -std=c++11 main.cpp -o maze_solver
   ```
2. Run the executable:
   ```bash
   ./maze_solver    # Linux/Mac
   .\maze_solver.exe # Windows
   ```


## Usage
```
Maze Solver CLI Tool
Usage: ./maze_solver <maze_file> [algorithm]
Algorithms:
  bfs    - Breadth-First Search (default)
  astar  - A* Search

Example:
  ./maze_solver maze.txt
  ./maze_solver maze.txt astar
```

## Example Output
```
Solving with BFS algorithm...
Maze Solution (12 steps):
#######
#S@@@E#
#@###@#
#@@@@@#
#######

Solved in 1 ms
```

## Key Functions
- `solveBFS()` — Finds shortest path using BFS.
- `solveAStar()` — Finds path using A* with Manhattan heuristic.
- `displaySolution(path)` — Prints maze with solution path (`@`).

## Notes
- The tool throws errors for missing files, empty mazes, or missing start/end points.
- Only orthogonal (no diagonal) moves are allowed.
- Modify the maze file to test different layouts.