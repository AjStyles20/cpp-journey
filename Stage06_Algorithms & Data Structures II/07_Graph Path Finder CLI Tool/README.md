# 07_Graph Path Finder CLI Tool

## Project Description
A command-line tool to find the shortest path between two nodes in a graph using either:
- **Breadth-First Search (BFS)** for unweighted graphs
- **Dijkstra's Algorithm** for weighted graphs

The graph is read from a text file, and the shortest path, total cost, and computation time are displayed.

---

## Features
- Supports both unweighted (BFS) and weighted (Dijkstra) shortest path search.
- Prints the path, node count, total cost, and computation time.
- Handles invalid input files and missing paths gracefully.

---

## Input File Format
Each line represents an edge:
- **Unweighted:**  
  `source destination`
- **Weighted:**  
  `source destination weight`

**Examples:**
```
A B
B C
C D
```
or
```
A B 5
B C 3
C D 2
```

---

## How to Run
1. Compile the program:
   ```bash
   g++ -std=c++11 main.cpp -o graph_path_finder
   ```
2. Run the executable:
   ```bash
   ./graph_path_finder    # Linux/Mac
   .\graph_path_finder.exe # Windows
   ```

## Usage
```
Graph Path Finder CLI Tool
Usage: ./AlgorithmComparison <graph_file> <start_node> <end_node> [--weighted]
Options:
  --weighted   Use Dijkstra's algorithm for weighted graphs (omit for BFS on unweighted graphs)

Input File Format:
  Each line represents an edge: source destination [weight]
  Example (unweighted):
    A B
    B C
  Example (weighted):
    A B 5
    B C 3
```

---

## Example Output
```
Shortest path (4 nodes): A -> B -> C -> D
Total cost: 10
Computation time: 0 ms
```

---

## Key Functions
- `shortestPathBFS(start, end)` — Finds shortest path in unweighted graphs.
- `shortestPathDijkstra(start, end)` — Finds shortest path in weighted graphs.
- `getPathCost(path)` — Computes total cost of the path.

---

## Notes
- The tool reports if no path exists between the given nodes.
- For undirected graphs, open `main.cpp` and in the `addEdge()` function, uncomment the line that adds the reverse edge, for example:
  ```cpp
  // adj[destination].push_back({source, weight}); // Uncomment for undirected graphs
  ```
- Node names are case-sensitive.
- Modify the input file to test different graphs.