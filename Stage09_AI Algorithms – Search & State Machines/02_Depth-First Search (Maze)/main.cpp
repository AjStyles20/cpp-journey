#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include <climits>
#include <algorithm>

using namespace std;

// Directions: up, down, left, right
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

// DFS using explicit stack (non-recursive)
pair<int, vector<Point>> dfsMazeSolver(const vector<vector<char>>& maze, 
                                      Point start, Point goal) {
    int rows = maze.size();
    if (rows == 0) return make_pair(-1, vector<Point>());
    int cols = maze[0].size();
    
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<Point>> parent(rows, vector<Point>(cols, Point(-1, -1)));
    stack<Point> s;
    
    s.push(start);
    visited[start.x][start.y] = true;
    
    while (!s.empty()) {
        Point current = s.top();
        s.pop();
        
        // Check if we've reached the goal
        if (current.x == goal.x && current.y == goal.y) {
            // Reconstruct path and calculate length
            vector<Point> path;
            Point at = goal;
            int length = 0;
            while (at.x != -1 && at.y != -1) {
                path.push_back(at);
                at = parent[at.x][at.y];
                length++;
            }
            reverse(path.begin(), path.end());
            return make_pair(length-1, path); // Subtract 1 since start counts as step 0
        }
        
        // Explore all 4 directions (order affects DFS path)
        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            
            // Check if new position is valid and not visited
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && 
                maze[nx][ny] != '#' && !visited[nx][ny]) {
                visited[nx][ny] = true;
                parent[nx][ny] = current;
                s.push(Point(nx, ny));
            }
        }
    }
    
    // No path found
    return make_pair(-1, vector<Point>());
}

// Same printing function as before
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
    // Same maze as BFS example for comparison
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
    
    auto dfsResult = dfsMazeSolver(maze, start, goal);
    int dfsPathLength = dfsResult.first;
    vector<Point> dfsPath = dfsResult.second;
    
    if (dfsPathLength == -1) {
        cout << "DFS: No path exists from start to goal!\n";
    } else {
        cout << "DFS Path length: " << dfsPathLength << "\n";
        cout << "DFS Path sequence:\n";
        for (const auto& p : dfsPath) {
            cout << "(" << p.x << ", " << p.y << ") ";
        }
        cout << "\n\nMaze with DFS path:\n";
        printMazeWithPath(maze, dfsPath);
    }
    
    return 0;
}