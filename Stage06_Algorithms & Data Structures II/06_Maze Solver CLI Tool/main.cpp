#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <limits>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Maze cell types
const char WALL = '#';
const char PATH = '.';
const char START = 'S';
const char END = 'E';
const char SOLUTION = '@';

struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    bool operator<(const Point& other) const {
        return tie(x, y) < tie(other.x, other.y);
    }
};

// For unordered_map
struct PointHash {
    size_t operator()(const Point& p) const {
        return hash<int>()(p.x) ^ hash<int>()(p.y);
    }
};

class MazeSolver {
private:
    vector<string> maze;
    Point start, end;
    int width, height;

    // Heuristic for A* (Manhattan distance)
    int heuristic(const Point& p) {
        return abs(p.x - end.x) + abs(p.y - end.y);
    }

    // Get valid neighboring points
    vector<Point> getNeighbors(const Point& p) {
        vector<Point> neighbors;
        for (int dx : {-1, 0, 1}) {
            for (int dy : {-1, 0, 1}) {
                if (dx == 0 && dy == 0) continue; // Skip self
                if (dx != 0 && dy != 0) continue; // Skip diagonals

                Point neighbor{p.x + dx, p.y + dy};
                if (neighbor.x >= 0 && neighbor.x < height &&
                    neighbor.y >= 0 && neighbor.y < width &&
                    maze[neighbor.x][neighbor.y] != WALL) {
                    neighbors.push_back(neighbor);
                }
            }
        }
        return neighbors;
    }

    // Reconstruct path from cameFrom map
    vector<Point> reconstructPath(const unordered_map<Point, Point, PointHash>& cameFrom) {
        vector<Point> path;
        Point current = end;
        while (!(current == start)) {
            path.push_back(current);
            current = cameFrom.at(current);
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
        return path;
    }

public:
    MazeSolver(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Could not open file: " + filename);
        }

        string line;
        while (getline(file, line)) {
            maze.push_back(line);
        }
        file.close();

        height = maze.size();
        if (height == 0) throw runtime_error("Empty maze");
        width = maze[0].size();

        // Find start and end points
        bool foundStart = false, foundEnd = false;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (maze[i][j] == START) {
                    start = {i, j};
                    foundStart = true;
                } else if (maze[i][j] == END) {
                    end = {i, j};
                    foundEnd = true;
                }
            }
        }

        if (!foundStart || !foundEnd) {
            throw runtime_error("Maze must have both start (S) and end (E) points");
        }
    }

    // Solve using BFS
    vector<Point> solveBFS() {
        queue<Point> frontier;
        frontier.push(start);
        
        unordered_map<Point, Point, PointHash> cameFrom;
        cameFrom[start] = start;

        while (!frontier.empty()) {
            Point current = frontier.front();
            frontier.pop();

            if (current == end) {
                return reconstructPath(cameFrom);
            }

            for (Point neighbor : getNeighbors(current)) {
                if (cameFrom.find(neighbor) == cameFrom.end()) {
                    frontier.push(neighbor);
                    cameFrom[neighbor] = current;
                }
            }
        }

        throw runtime_error("No path exists in maze");
    }

    // Solve using A*
    vector<Point> solveAStar() {
        auto cmp = [&](const pair<Point, int>& a, const pair<Point, int>& b) {
            return a.second > b.second;
        };
        priority_queue<pair<Point, int>, vector<pair<Point, int>>, decltype(cmp)> frontier(cmp);
        frontier.push({start, 0});

        unordered_map<Point, Point, PointHash> cameFrom;
        unordered_map<Point, int, PointHash> costSoFar;
        cameFrom[start] = start;
        costSoFar[start] = 0;

        while (!frontier.empty()) {
            Point current = frontier.top().first;
            frontier.pop();

            if (current == end) {
                return reconstructPath(cameFrom);
            }

            for (Point neighbor : getNeighbors(current)) {
                int newCost = costSoFar[current] + 1;
                if (costSoFar.find(neighbor) == costSoFar.end() || newCost < costSoFar[neighbor]) {
                    costSoFar[neighbor] = newCost;
                    int priority = newCost + heuristic(neighbor);
                    frontier.push({neighbor, priority});
                    cameFrom[neighbor] = current;
                }
            }
        }

        throw runtime_error("No path exists in maze");
    }

    // Display maze with solution path
    void displaySolution(const vector<Point>& path) {
        vector<string> solutionMaze = maze;
        
        // Mark solution path (skip start and end)
        for (size_t i = 1; i < path.size() - 1; i++) {
            Point p = path[i];
            solutionMaze[p.x][p.y] = SOLUTION;
        }

        cout << "Maze Solution (" << path.size() << " steps):\n";
        for (const string& row : solutionMaze) {
            cout << row << "\n";
        }
    }
};

void showUsage() {
    cout << "Maze Solver CLI Tool\n"
         << "Usage: ./maze_solver <maze_file> [algorithm]\n"
         << "Algorithms:\n"
         << "  bfs    - Breadth-First Search (default)\n"
         << "  astar  - A* Search\n\n"
         << "Example:\n"
         << "  ./maze_solver maze.txt\n"
         << "  ./maze_solver maze.txt astar\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        showUsage();
        return 1;
    }

    try {
        string filename = argv[1];
        string algorithm = (argc > 2) ? argv[2] : "bfs";

        MazeSolver solver(filename);
        vector<Point> path;

        auto start = chrono::high_resolution_clock::now();
        
        if (algorithm == "astar") {
            cout << "Solving with A* algorithm...\n";
            path = solver.solveAStar();
        } else {
            cout << "Solving with BFS algorithm...\n";
            path = solver.solveBFS();
        }

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        solver.displaySolution(path);
        cout << "\nSolved in " << duration.count() << " ms\n";

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}