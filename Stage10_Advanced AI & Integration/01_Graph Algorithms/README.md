# 01_Graph Algorithms: Dijkstra vs. A* Pathfinding

## Description

This project demonstrates and compares two fundamental graph search algorithms—Dijkstra's algorithm and A* (A-star) pathfinding—on a sample road network. The program computes the shortest path between two nodes using both algorithms, measures their execution time, and compares their results.

---

## Features

- Defines a weighted, undirected graph with nodes and edges
- Implements Dijkstra's algorithm for shortest path search
- Implements A* algorithm with Euclidean distance heuristic
- Prints the path, total distance, and computation time for each algorithm
- Compares the results and reports which algorithm was faster

---

## How to Run

1. **Compile the code:**
   ```bash
   g++ main.cpp -o graph_algorithms -std=c++11
   ```

2. **Run the program:**
   ```bash
   ./graph_algorithms
   ```
   or on Windows:
   ```powershell
   .\graph_algorithms.exe
   ```

---

## Example Output

```
Comparing Dijkstra and A* algorithms
Start: Node 0, Goal: Node 4

Dijkstra's Algorithm:
  Path: 0 1 2 4 
  Distance: 8.9
  Time: 0.12 ms

A* Algorithm:
  Path: 0 1 2 4 
  Distance: 8.9
  Time: 0.04 ms

Comparison:
  Both algorithms found paths with the same distance: Yes
  A* was 3x faster
```

---

## Learning Objectives

- Understand and implement Dijkstra's and A* algorithms for shortest pathfinding
- Learn about graph representation and traversal in C++
- Compare the efficiency and results of different pathfinding strategies
- Practice using priority queues, heuristics, and path reconstruction

---

This project provides a practical introduction to graph algorithms and performance comparison in C++.