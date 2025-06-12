#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <iomanip>
#include <algorithm>

using namespace std;

// Grid cell definition
struct Cell {
    int x, y;
    bool operator==(const Cell& other) const {
        return x == other.x && y == other.y;
    }
    bool operator<(const Cell& other) const {
        return make_pair(x, y) < make_pair(other.x, other.y);
    }
};

// Hash function for Cell
struct CellHash {
    size_t operator()(const Cell& c) const {
        return hash<int>()(c.x) ^ hash<int>()(c.y);
    }
};

class GridPathfinder {
private:
    vector<vector<bool>> grid; // true = obstacle
    int rows, cols;
    
    // Heuristic function (Manhattan distance)
    int heuristic(const Cell& a, const Cell& b) {
        return abs(a.x - b.x) + abs(a.y - b.y);
    }
    
    // Check if cell is valid
    bool isValid(const Cell& c) {
        return c.x >= 0 && c.x < rows && c.y >= 0 && c.y < cols && !grid[c.x][c.y];
    }
    
    // Get neighboring cells
    vector<Cell> getNeighbors(const Cell& c) {
        vector<Cell> neighbors;
        for (int dx : {-1, 0, 1}) {
            for (int dy : {-1, 0, 1}) {
                if (dx == 0 && dy == 0) continue; // Skip self
                if (dx != 0 && dy != 0) continue; // Skip diagonals for 4-directional
                
                Cell neighbor{c.x + dx, c.y + dy};
                if (isValid(neighbor)) {
                    neighbors.push_back(neighbor);
                }
            }
        }
        return neighbors;
    }
    
    // Reconstruct path from parent pointers
    vector<Cell> reconstructPath(const Cell& start, const Cell& end, 
                                const unordered_map<Cell, Cell, CellHash>& parent) {
        vector<Cell> path;
        Cell current = end;
        while (!(current == start)) {
            path.push_back(current);
            current = parent.at(current);
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
        return path;
    }

public:
    GridPathfinder(int r, int c) : rows(r), cols(c), grid(r, vector<bool>(c, false)) {}
    
    // Add obstacle
    void addObstacle(int x, int y) {
        grid[x][y] = true;
    }
    
    // DFS Pathfinding (returns path or empty vector if none found)
    vector<Cell> findPathDFS(Cell start, Cell end) {
        unordered_set<Cell, CellHash> visited;
        stack<Cell> s;
        unordered_map<Cell, Cell, CellHash> parent;
        bool found = false;
        
        s.push(start);
        visited.insert(start);
        
        while (!s.empty() && !found) {
            Cell current = s.top();
            s.pop();
            
            if (current == end) {
                found = true;
                break;
            }
            
            for (Cell neighbor : getNeighbors(current)) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    parent[neighbor] = current;
                    s.push(neighbor);
                }
            }
        }
        
        return found ? reconstructPath(start, end, parent) : vector<Cell>();
    }
    
    // Greedy Best-First Search (heuristic-guided)
    vector<Cell> findPathGreedy(Cell start, Cell end) {
        unordered_set<Cell, CellHash> visited;
        auto cmp = [&](const Cell& a, const Cell& b) {
            return heuristic(a, end) > heuristic(b, end);
        };
        priority_queue<Cell, vector<Cell>, decltype(cmp)> pq(cmp);
        unordered_map<Cell, Cell, CellHash> parent;
        bool found = false;
        
        pq.push(start);
        visited.insert(start);
        
        while (!pq.empty() && !found) {
            Cell current = pq.top();
            pq.pop();
            
            if (current == end) {
                found = true;
                break;
            }
            
            for (Cell neighbor : getNeighbors(current)) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    parent[neighbor] = current;
                    pq.push(neighbor);
                }
            }
        }
        
        return found ? reconstructPath(start, end, parent) : vector<Cell>();
    }
    
    // Display grid with path
    void displayGridWithPath(const vector<Cell>& path) {
        unordered_set<Cell, CellHash> pathCells(path.begin(), path.end());
        
        cout << "Grid (" << rows << "×" << cols << "):\n";
        cout << "  ";
        for (int y = 0; y < cols; y++) cout << setw(2) << y;
        cout << "\n";
        
        for (int x = 0; x < rows; x++) {
            cout << setw(2) << x << " ";
            for (int y = 0; y < cols; y++) {
                Cell c{x, y};
                if (grid[x][y]) {
                    cout << "██";
                } else if (pathCells.find(c) != pathCells.end()) {
                    cout << "◍◍";
                } else {
                    cout << "░░";
                }
            }
            cout << "\n";
        }
    }
};

int main() {
    // Create a 10x10 grid
    GridPathfinder pathfinder(10, 10);
    
    // Add some obstacles
    for (int i = 2; i < 9; i++) pathfinder.addObstacle(i, 5);
    pathfinder.addObstacle(4, 3);
    pathfinder.addObstacle(4, 4);
    pathfinder.addObstacle(5, 7);
    pathfinder.addObstacle(6, 7);
    
    // Define start and end points
    Cell start{0, 0}, end{9, 9};
    
    // Find and display paths
    cout << "DFS Path:\n";
    vector<Cell> dfsPath = pathfinder.findPathDFS(start, end);
    pathfinder.displayGridWithPath(dfsPath);
    
    cout << "\nGreedy Best-First Path:\n";
    vector<Cell> greedyPath = pathfinder.findPathGreedy(start, end);
    pathfinder.displayGridWithPath(greedyPath);
    
    return 0;
}