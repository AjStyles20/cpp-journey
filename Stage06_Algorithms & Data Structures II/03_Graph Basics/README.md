# 03_Graph Basics

## Project Description
This project demonstrates the fundamentals of graph data structures and traversal algorithms in C++. It includes:
- Graph representation using adjacency lists
- Adding edges (undirected)
- Breadth-First Search (BFS)
- Depth-First Search (DFS), both iterative and recursive

## Learning Objectives
- Understand graph representation with adjacency lists
- Implement and compare BFS and DFS traversals
- Recognize the difference between iterative and recursive DFS
- Observe traversal order and the effect of cycles in graphs

## Technologies Used
- **C++11** (or later)
- **STL Containers**: `vector`, `queue`, `stack`
- **Visual Studio Code** (with C/C++ extension)

## How to Run
1. Compile the program:
   ```bash
   g++ -std=c++11 main.cpp -o GraphBasics
   ```
2. Run the executable:
   ```bash
   ./GraphBasics    # Linux/Mac
   .\GraphBasics.exe # Windows
   ```

## How It Works

- The program creates a graph with 7 vertices (0 to 6).
- Edges are added to form a connected, undirected graph with a cycle.
- The following traversals are performed from node 0:
  - **BFS** (Breadth-First Search)
  - **DFS** (Depth-First Search, iterative)
  - **DFSRecursive** (Depth-First Search, recursive)

## Example Output
```
BFS starting from node 0: 0 1 2 3 4 5 6 
DFS starting from node 0: 0 1 3 4 5 2 6 
DFS (Recursive) starting from node 0: 0 1 3 4 5 2 6 
```

## Key Functions

- `addEdge(int u, int v)` — Adds an undirected edge between nodes `u` and `v`
- `BFS(int start)` — Performs iterative breadth-first traversal
- `DFS(int start)` — Performs iterative depth-first traversal
- `DFSRecursive(int start)` — Performs recursive depth-first traversal

## Graph Structure Used

```
      0
     / \
    1   2
   / \ / \
  3  4 5  6
      \ /
       5
```
- The edge between 4 and 5 creates a cycle.

## Key Concepts
- **Adjacency List**: Efficient graph representation for sparse graphs
- **BFS**: Explores neighbors level by level (uses a queue)
- **DFS**: Explores as far as possible along each branch before backtracking (uses a stack or recursion)
- **Cycle Handling**: Visited array prevents infinite loops

## Notes
- The graph is undirected; to make it directed, remove the second `adjList[v].push_back(u);` in `addEdge`.
- You can modify the number of vertices and edges to experiment with different graph structures.
- The traversal order may vary depending on the order of neighbors in the adjacency list.

