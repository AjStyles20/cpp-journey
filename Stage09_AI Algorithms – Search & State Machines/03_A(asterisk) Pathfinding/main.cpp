#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;

// Directions: up, down, left, right
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// Node for priority queue
struct Node {
    Point point;
    int f, g, h;
    
    Node(Point p, int g, int h) : point(p), g(g), h(h), f(g + h) {}
    
    // Comparison operator for priority queue (min-heap)
    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

// Manhattan distance heuristic
int manhattanDistance(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// A* pathfinding algorithm
pair<int, vector<Point>> aStarSearch(const vector<vector<char>>& maze, 
                                    Point start, Point goal) {
    int rows = maze.size();
    if (rows == 0) return make_pair(-1, vector<Point>());
    int cols = maze[0].size();
    
    // Priority queue (min-heap) for open set
    priority_queue<Node, vector<Node>, greater<Node>> openSet;
    
    // Create matrices for tracking
    vector<vector<bool>> closedSet(rows, vector<bool>(cols, false));
    vector<vector<int>> gScore(rows, vector<int>(cols, INT_MAX));
    vector<vector<int>> fScore(rows, vector<int>(cols, INT_MAX));
    vector<vector<Point>> cameFrom(rows, vector<Point>(cols, Point(-1, -1)));
    
    // Initialize starting node
    gScore[start.x][start.y] = 0;
    fScore[start.x][start.y] = manhattanDistance(start, goal);
    openSet.push(Node(start, 0, fScore[start.x][start.y]));
    
    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();
        
        // Check if we've reached the goal
        if (current.point == goal) {
            // Reconstruct path
            vector<Point> path;
            Point at = goal;
            while (!(at == Point(-1, -1))) {
                path.push_back(at);
                at = cameFrom[at.x][at.y];
            }
            reverse(path.begin(), path.end());
            return make_pair(gScore[goal.x][goal.y], path);
        }
        
        // Skip if we already found a better path to this node
        if (closedSet[current.point.x][current.point.y]) continue;
        closedSet[current.point.x][current.point.y] = true;
        
        // Explore neighbors
        for (int i = 0; i < 4; i++) {
            Point neighbor(current.point.x + dx[i], current.point.y + dy[i]);
            
            // Check bounds and walkability
            if (neighbor.x < 0 || neighbor.x >= rows || 
                neighbor.y < 0 || neighbor.y >= cols || 
                maze[neighbor.x][neighbor.y] == '#') {
                continue;
            }
            
            // Calculate tentative gScore
            int tentativeGScore = gScore[current.point.x][current.point.y] + 1;
            
            // If we found a better path to this neighbor
            if (tentativeGScore < gScore[neighbor.x][neighbor.y]) {
                cameFrom[neighbor.x][neighbor.y] = current.point;
                gScore[neighbor.x][neighbor.y] = tentativeGScore;
                fScore[neighbor.x][neighbor.y] = tentativeGScore + manhattanDistance(neighbor, goal);
                
                // Add to open set
                openSet.push(Node(neighbor, gScore[neighbor.x][neighbor.y], 
                            manhattanDistance(neighbor, goal)));
            }
        }
    }
    
    // No path found
    return make_pair(-1, vector<Point>());
}

void printMazeWithPath(const vector<vector<char>>& maze, const vector<Point>& path) {
    vector<vector<char>> mazeCopy = maze;
    
    // Mark the path (excluding start and end)
    for (size_t i = 1; i + 1 < path.size(); i++) {
        mazeCopy[path[i].x][path[i].y] = '*';
    }
    
    // Print the maze
    for (const auto& row : mazeCopy) {
        for (char cell : row) {
            cout << cell << ' ';
        }
        cout << '\n';
    }
}

int main() {
    // Example maze (S = start, G = goal, # = wall, . = path)
    vector<vector<char>> maze = {
        {'S', '.', '#', '#', '.', '.', '.', '#', '.', 'G'},
        {'#', '.', '#', '#', '.', '#', '.', '#', '.', '#'},
        {'#', '.', '.', '.', '.', '#', '.', '.', '.', '#'},
        {'#', '#', '#', '#', '.', '#', '#', '#', '.', '#'},
        {'#', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };
    
    // Find start and goal positions
    Point start, goal;
    for (size_t i = 0; i < maze.size(); i++) {
        for (size_t j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == 'S') start = Point(i, j);
            if (maze[i][j] == 'G') goal = Point(i, j);
        }
    }
    
    auto result = aStarSearch(maze, start, goal);
    int pathLength = result.first;
    vector<Point> path = result.second;
    
    if (pathLength == -1) {
        cout << "No path exists from start to goal!\n";
    } else {
        cout << "A* Path length: " << pathLength << "\n";
        cout << "Path sequence:\n";
        for (const auto& p : path) {
            cout << "(" << p.x << ", " << p.y << ") ";
        }
        cout << "\n\nMaze with A* path:\n";
        printMazeWithPath(maze, path);
    }
    
    return 0;
}