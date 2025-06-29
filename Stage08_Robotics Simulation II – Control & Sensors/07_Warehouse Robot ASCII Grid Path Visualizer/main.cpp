#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 5;

// Cell types
enum Cell {
    EMPTY, OBSTACLE, ROBOT, TARGET
};

// Grid and robot state
vector<vector<Cell>> grid(HEIGHT, vector<Cell>(WIDTH, EMPTY));

struct Position {
    int x, y;
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

Position robotPos = {0, 0};
Position targetPos = {7, 2};

// Directions for movement: up, down, left, right
vector<pair<int, int>> directions = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}
};

// Render the ASCII grid
void renderGrid() {
    system("clear"); // or "cls" on Windows
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (robotPos.x == x && robotPos.y == y) cout << "R ";
            else if (targetPos.x == x && targetPos.y == y) cout << "T ";
            else if (grid[y][x] == OBSTACLE) cout << "X ";
            else cout << ". ";
        }
        cout << endl;
    }
    cout << endl;
}

// BFS for pathfinding
vector<Position> bfs(Position start, Position goal) {
    vector<vector<bool>> visited(HEIGHT, vector<bool>(WIDTH, false));
    vector<vector<Position>> parent(HEIGHT, vector<Position>(WIDTH));

    queue<Position> q;
    q.push(start);
    visited[start.y][start.x] = true;

    while (!q.empty()) {
        Position cur = q.front(); q.pop();
        if (cur == goal) break;

        for (auto [dy, dx] : directions) {
            int nx = cur.x + dx;
            int ny = cur.y + dy;

            if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT &&
                !visited[ny][nx] && grid[ny][nx] != OBSTACLE) {
                visited[ny][nx] = true;
                parent[ny][nx] = cur;
                q.push({nx, ny});
            }
        }
    }

    // Reconstruct path
    vector<Position> path;
    if (!visited[goal.y][goal.x]) return path; // no path

    for (Position p = goal; !(p == start); p = parent[p.y][p.x]) {
        path.push_back(p);
    }
    reverse(path.begin(), path.end());
    return path;
}

// Simulate movement step-by-step
void moveRobotAlongPath(const vector<Position>& path) {
    for (const auto& step : path) {
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        renderGrid();
        this_thread::sleep_for(chrono::milliseconds(400));
    }
}

// Add random obstacles
void placeObstacles(int count) {
    srand(time(0));
    while (count > 0) {
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;
        if ((x == robotPos.x && y == robotPos.y) ||
            (x == targetPos.x && y == targetPos.y) ||
            grid[y][x] == OBSTACLE) continue;
        grid[y][x] = OBSTACLE;
        count--;
    }
}

int main() {
    placeObstacles(12);
    renderGrid();
    cout << "Planning path..." << endl;
    vector<Position> path = bfs(robotPos, targetPos);

    if (path.empty()) {
        cout << "No path found to target!\n";
        return 1;
    }

    cout << "Path found! Moving robot...\n";
    moveRobotAlongPath(path);
    cout << "Target reached!\n";
    return 0;
}
