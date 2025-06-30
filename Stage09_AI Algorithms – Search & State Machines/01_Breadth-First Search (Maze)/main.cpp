#include <iostream>
#include <vector>
#include <queue>
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

// Function to perform BFS and find shortest path
pair<int, vector<Point>> bfsMazeSolver(const vector<vector<char>>& maze, 
                                      Point start, Point goal) {
    int rows = maze.size();
    if (rows == 0) return make_pair(-1, vector<Point>());
    int cols = maze[0].size();
    
    // Create visited matrix and distance matrix
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<int>> distance(rows, vector<int>(cols, INT_MAX));
    vector<vector<Point>> parent(rows, vector<Point>(cols, Point(-1, -1)));
    
    queue<Point> q;
    q.push(start);
    visited[start.x][start.y] = true;
    distance[start.x][start.y] = 0;
    
    while (!q.empty()) {
        Point current = q.front();
        q.pop();
        
        // Check if we've reached the goal
        if (current.x == goal.x && current.y == goal.y) {
            // Reconstruct path
            vector<Point> path;
            Point at = goal;
            while (at.x != -1 && at.y != -1) {
                path.push_back(at);
                at = parent[at.x][at.y];
            }
            reverse(path.begin(), path.end());
            return make_pair(distance[goal.x][goal.y], path);
        }
        
        // Explore all 4 directions
        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            
            // Check if new position is valid and not visited
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && 
                maze[nx][ny] != '#' && !visited[nx][ny]) {
                visited[nx][ny] = true;
                distance[nx][ny] = distance[current.x][current.y] + 1;
                parent[nx][ny] = current;
                q.push(Point(nx, ny));
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
        mazeCopy[path[i].x][path[i].y] = '.';
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
    
    auto result = bfsMazeSolver(maze, start, goal);
    int pathLength = result.first;
    vector<Point> path = result.second;
    
    if (pathLength == -1) {
        cout << "No path exists from start to goal!\n";
    } else {
        cout << "Shortest path length: " << pathLength << "\n";
        cout << "Path sequence:\n";
        for (const auto& p : path) {
            cout << "(" << p.x << ", " << p.y << ") ";
        }
        cout << "\n\nMaze with path:\n";
        printMazeWithPath(maze, path);
    }
    
    return 0;
}