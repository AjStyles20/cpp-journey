#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std;

const int WIDTH = 8;
const int HEIGHT = 6;
const int MAX_STEPS = 30;

struct Position {
    int x, y;
    bool operator==(const Position& other) const { return x == other.x && y == other.y; }
    bool operator!=(const Position& other) const { return !(*this == other); }
    bool operator<(const Position& other) const { return tie(y, x) < tie(other.y, other.x); }
};

// Directions: Up, Down, Left, Right
vector<Position> directions = {{0,-1},{0,1},{-1,0},{1,0}};

struct Robot {
    int id;
    Position pos;
    Position goal;
    vector<Position> path;
    bool reached = false;
};

vector<vector<char>> grid(HEIGHT, vector<char>(WIDTH, '.'));
map<int, Robot> robots;
set<Position> obstacles;
map<Position, int> reservations;

void printGrid() {
    system("clear");
    vector<vector<char>> display = grid;
    for (const auto& [id, robot] : robots) {
        if (!robot.reached)
            display[robot.pos.y][robot.pos.x] = '0' + id;
        else
            display[robot.pos.y][robot.pos.x] = 'G';
    }
    for (auto& row : display) {
        for (char c : row) cout << c << ' ';
        cout << '\n';
    }
    cout << endl;
}

// Basic BFS pathfinding
vector<Position> bfs(Position start, Position goal) {
    queue<Position> q;
    map<Position, Position> parent;
    set<Position> visited;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        Position curr = q.front(); q.pop();
        if (curr == goal) break;

        for (auto d : directions) {
            Position next{curr.x + d.x, curr.y + d.y};
            if (next.x >= 0 && next.x < WIDTH && next.y >= 0 && next.y < HEIGHT &&
                !visited.count(next) && !obstacles.count(next)) {
                visited.insert(next);
                parent[next] = curr;
                q.push(next);
            }
        }
    }

    if (!parent.count(goal)) return {};

    vector<Position> path;
    for (Position p = goal; p != start; p = parent[p]) path.push_back(p);
    reverse(path.begin(), path.end());
    return path;
}

// Move all robots one step if possible
void stepSimulation(int step) {
    set<Position> next_positions;
    map<int, Position> proposed_moves;

    // First, plan moves
    for (auto& [id, robot] : robots) {
        if (robot.reached || robot.path.empty()) continue;
        Position next = robot.path.front();
        if (!reservations.count(next)) {
            proposed_moves[id] = next;
            next_positions.insert(next);
        }
    }

    // Apply moves
    for (auto& [id, pos] : proposed_moves) {
        robots[id].pos = pos;
        robots[id].path.erase(robots[id].path.begin());
        reservations[pos] = step;
        if (robots[id].pos == robots[id].goal) {
            robots[id].reached = true;
        }
    }
}

int main() {
    // Setup obstacles (optional)
    obstacles.insert({3,2}); obstacles.insert({3,3});
    grid[2][3] = grid[3][3] = 'X';

    // Define robots
    robots[1] = {1, {0, 0}, {7, 0}};
    robots[2] = {2, {7, 5}, {0, 5}};

    // Compute paths
    for (auto& [id, robot] : robots) {
        robot.path = bfs(robot.pos, robot.goal);
        if (robot.path.empty()) {
            cout << "No path found for robot " << id << endl;
        }
    }

    for (int step = 0; step < MAX_STEPS; step++) {
        printGrid();
        cout << "Step: " << step << endl;
        stepSimulation(step);
        this_thread::sleep_for(chrono::milliseconds(500));

        bool all_done = true;
        for (auto& [_, robot] : robots) if (!robot.reached) all_done = false;
        if (all_done) break;
    }

    cout << "Simulation Complete." << endl;
    return 0;
}
