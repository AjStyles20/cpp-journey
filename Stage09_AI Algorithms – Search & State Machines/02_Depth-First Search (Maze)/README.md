# 02_Depth-First Search (Maze)

## Description

This project demonstrates how to use the Depth-First Search (DFS) algorithm to find a path in a maze. The maze is represented as a 2D grid with walls, open spaces, a start point (`S`), and a goal point (`G`). The program finds a path from the start to the goal (not necessarily the shortest), prints the path sequence, and visualizes the path on the maze using ASCII art.

---

## Features

- 2D maze representation with walls (`#`), open cells (`.`), start (`S`), and goal (`G`)
- DFS algorithm (using an explicit stack) to find a path from start to goal
- Prints the path length and the sequence of coordinates
- ASCII visualization of the maze with the path marked

---

## How to Run

1. **Compile the code:**
   ```bash
   g++ main.cpp -o dfs_maze -std=c++11
   ```

2. **Run the program:**
   ```bash
   ./dfs_maze
   ```
   or on Windows:
   ```powershell
   .\dfs_maze.exe
   ```

---

## Example Output

```
DFS Path length: 17
DFS Path sequence:
(0, 0) (1, 1) (2, 1) (2, 2) ... (0, 9)

Maze with DFS path:
S . # # . . . # . G 
# . # # . # . # . # 
# . * * * # . . . # 
# # # # * # # # . # 
# . . . * * * * * # 
# # # # # # # # # # 
```

---

## Learning Objectives

- Understand and implement the DFS algorithm for pathfinding
- Represent and manipulate 2D grid mazes in C++
- Visualize search results and paths in the terminal
- Practice using stacks and parent tracking for path reconstruction

---

## Possible Extensions

- Allow user input for custom mazes
- Support for diagonal movement or weighted cells
- Visualize the search process step-by-step
- Implement other search algorithms (BFS, A*, Dijkstra)

---

This project provides a hands-on introduction to