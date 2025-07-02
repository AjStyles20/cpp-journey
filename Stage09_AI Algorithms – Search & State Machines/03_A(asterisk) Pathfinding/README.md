# 03_A* Pathfinding (Maze)

## Description

This project demonstrates the A* (A-star) pathfinding algorithm to find the shortest path in a maze. The maze is represented as a 2D grid with walls, open spaces, a start point (`S`), and a goal point (`G`). The program finds the shortest path from the start to the goal using the Manhattan distance heuristic, prints the path sequence, and visualizes the path on the maze using ASCII art.

---

## Features

- 2D maze representation with walls (`#`), open cells (`.`), start (`S`), and goal (`G`)
- A* algorithm for optimal shortest path search
- Uses Manhattan distance as the heuristic
- Prints the path length and the sequence of coordinates
- ASCII visualization of the maze with the path marked (`*`)

---

## How to Run

1. **Compile the code:**
   ```bash
   g++ main.cpp -o astar_maze -std=c++11
   ```

2. **Run the program:**
   ```bash
   ./astar_maze
   ```
   or on Windows:
   ```powershell
   .\astar_maze.exe
   ```

---

## Example Output

```
A* Path length: 17
Path sequence:
(0, 0) (1, 1) (2, 1) (2, 2) ... (0, 9)

Maze with A* path:
S . # # . . . # . G 
# * # # . # . # . # 
# * * * * # . . . # 
# # # # * # # # . # 
# . . . * * * * * # 
# # # # # # # # # # 
```

---

## Learning Objectives

- Understand and implement the A* algorithm for shortest pathfinding
- Represent and manipulate 2D grid mazes in C++
- Visualize search results and paths in the terminal
- Practice using priority queues and heuristics for efficient search

---

This project provides a hands-on introduction to heuristic search algorithms and optimal pathfinding in grid-based environments using C++.