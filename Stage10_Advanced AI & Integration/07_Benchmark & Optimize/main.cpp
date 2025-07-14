// Benchmark & Optimize: Timing BFS Pathfinding in Multi-Robot Grid
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

const int WIDTH = 30;
const int HEIGHT = 20;

struct Position {
    int x, y;
    bool operator==(const Position& other) const { return x == other.x && y == other.y; }
    bool operator!=(const Position& other) const { return !(*this == other); }
    bool operator<(const Position& other) const { return tie(y, x) < tie(other.y, other.x); }
};

vector<Position> directions = {{0,-1},{0,1},{-1,0},{1,0}};

// Benchmark BFS time for multiple start-goal pairs
vector<Position> bfs(const Position& start, const Position& goal, const set<Position>& obstacles) {
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

int main() {
    set<Position> obstacles;
    for (int i = 5; i < 25; ++i) obstacles.insert({i, 10}); // Add a long wall

    vector<pair<Position, Position>> testCases = {
        {{0, 0}, {29, 0}},
        {{0, 0}, {29, 19}},
        {{0, 0}, {0, 19}},
        {{10, 5}, {25, 15}},
        {{15, 3}, {3, 15}},
        {{0, 0}, {29, 10}},
        {{0, 19}, {29, 0}},
    };

    double totalTime = 0;
    int count = 0;

    for (auto& [start, goal] : testCases) {
        auto begin = high_resolution_clock::now();
        vector<Position> path = bfs(start, goal, obstacles);
        auto end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end - begin).count();
        totalTime += duration;
        ++count;

        cout << "BFS from (" << start.x << "," << start.y << ") to (" << goal.x << "," << goal.y << ")"
             << " took " << duration << " microseconds.\n";
        if (path.empty()) cout << "  => No path found.\n";
        else cout << "  => Path length: " << path.size() << "\n";
    }

    cout << "\nAverage time per BFS: " << (totalTime / count) << " microseconds.\n";
    return 0;
}
