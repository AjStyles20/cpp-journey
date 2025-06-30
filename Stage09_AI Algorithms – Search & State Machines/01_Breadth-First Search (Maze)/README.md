# 01_Breadth-First Search (Maze)

## Description

This project demonstrates how to use the Breadth-First Search (BFS) algorithm to find the shortest path in a maze. The maze is represented as a 2D grid with walls, open spaces, a start point (`S`), and a goal point (`G`). The program finds the shortest path from the start to the goal, prints the path sequence, and visualizes the path on the maze using ASCII art.

---

## Features

- 2D maze representation with walls (`#`), open cells (`.`), start (`S`), and goal (`G`)
- BFS algorithm to find the shortest path from start to goal
- Prints the path length and the sequence of coordinates
- ASCII visualization of the maze with the path marked

---

## How to Run

1. **Compile the code:**
   ```bash
   g++ main.cpp -o bfs_maze -std=c++11
   ```

2. **Run the program:**
   ```bash
   ./bfs_maze
   ```
   or on Windows:
   ```powershell
   .\bfs_maze.exe
   ```

---

## Example Output

```
Shortest path length: 17
Path sequence:
(0, 0) (1, 1) (2, 1) (2, 2) ... (0, 9)

Maze with path:
S . # # . . . # . G 
# . # # . # . # . # 
# . . . . # . . . # 
# # # # . # # # . # 
# . . . . . . . . # 
# # # # # # # # # # 
```

---

## Learning Objectives

- Understand and implement the BFS algorithm for shortest path finding
- Represent and manipulate 2D grid mazes in C++
- Visualize search results and paths in the terminal
- Practice using queues and parent tracking for path reconstruction

---

This project provides a hands-on introduction to search algorithms and pathfinding in grid-based environments using C++.