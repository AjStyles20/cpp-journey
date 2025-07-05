#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <thread>
#include <chrono>
#include <memory>
#include <algorithm>

using namespace std;

// Constants
const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 9;
const double ROBOT_SPEED = 0.5; // cells per second
const double TURN_RATE = 90.0; // degrees per second
const double CONTROL_LOOP_HZ = 10.0;

// Map symbols
const char EMPTY = '.';
const char WALL = '#';
const char START = 'S';
const char GOAL = 'G';
const char ROBOT = 'R';
const char PATH = '*';

// Robot orientation
enum class Orientation { NORTH, EAST, SOUTH, WEST };

// Point structure
struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// Node for pathfinding
struct Node {
    Point point;
    int g, h, f;
    shared_ptr<Node> parent;
    
    Node(Point p, int g, int h, shared_ptr<Node> parent = nullptr)
        : point(p), g(g), h(h), f(g+h), parent(parent) {}
    
    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

// Robot class
class AutonomousRobot {
private:
    Point position;
    Orientation orientation;
    vector<Point> path;
    size_t pathIndex;
    bool moving;
    
    // Helper function to calculate Manhattan distance
    int manhattanDistance(Point a, Point b) {
        return abs(a.x - b.x) + abs(a.y - b.y);
    }
    
    // A* pathfinding algorithm
    vector<Point> findPath(const vector<vector<char>>& map, Point start, Point goal) {
        priority_queue<Node, vector<Node>, greater<Node>> openSet;
        vector<vector<bool>> closedSet(MAP_HEIGHT, vector<bool>(MAP_WIDTH, false));
        
        openSet.emplace(start, 0, manhattanDistance(start, goal));
        
        while (!openSet.empty()) {
            Node current = openSet.top();
            openSet.pop();
            
            if (current.point == goal) {
                // Reconstruct path
                vector<Point> path;
                shared_ptr<Node> node = make_shared<Node>(current);
                while (node) {
                    path.push_back(node->point);
                    node = node->parent;
                }
                reverse(path.begin(), path.end());
                return path;
            }
            
            closedSet[current.point.y][current.point.x] = true;
            
            // Check neighbors (up, down, left, right)
            vector<Point> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};
            for (const auto& dir : directions) {
                Point neighbor(current.point.x + dir.x, current.point.y + dir.y);
                
                // Check bounds and walkability
                if (neighbor.x < 0 || neighbor.x >= MAP_WIDTH ||
                    neighbor.y < 0 || neighbor.y >= MAP_HEIGHT ||
                    map[neighbor.y][neighbor.x] == WALL ||
                    closedSet[neighbor.y][neighbor.x]) {
                    continue;
                }
                
                int g = current.g + 1;
                int h = manhattanDistance(neighbor, goal);
                openSet.emplace(neighbor, g, h, make_shared<Node>(current));
            }
        }
        
        return {}; // No path found
    }
    
    // Calculate required orientation to face target
    Orientation calculateDesiredOrientation(Point target) {
        int dx = target.x - position.x;
        int dy = target.y - position.y;
        
        if (abs(dx) > abs(dy)) {
            return dx > 0 ? Orientation::EAST : Orientation::WEST;
        } else {
            return dy > 0 ? Orientation::SOUTH : Orientation::NORTH;
        }
    }
    
    // Turn toward desired orientation
    bool adjustOrientation(Orientation desired) {
        if (orientation == desired) return true;
        
        // Simple turning logic
        int current = static_cast<int>(orientation);
        int target = static_cast<int>(desired);
        int diff = (target - current + 4) % 4;
        
        if (diff == 1 || diff == 3) {
            // Turn right or left
            orientation = static_cast<Orientation>((current + 1) % 4);
        } else if (diff == 2) {
            // Turn around (arbitrarily choose right)
            orientation = static_cast<Orientation>((current + 1) % 4);
        }
        
        return orientation == desired;
    }
    
public:
    AutonomousRobot() : pathIndex(0), moving(false), orientation(Orientation::NORTH) {}
    
    // Initialize robot with map
    void initialize(const vector<vector<char>>& map) {
        Point start, goal;
        
        // Find start and goal positions
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (map[y][x] == START) start = Point(x, y);
                if (map[y][x] == GOAL) goal = Point(x, y);
            }
        }
        
        position = start;
        path = findPath(map, start, goal);
        
        if (path.empty()) {
            cout << "No valid path found from start to goal!\n";
        } else {
            cout << "Path found with " << path.size() << " steps\n";
            moving = true;
            pathIndex = 1; // Start at first path point (start is at 0)
        }
    }
    
    // Update robot state
    void update(double dt) {
        if (!moving || pathIndex >= path.size()) return;
        
        Point target = path[pathIndex];
        Orientation desiredOrientation = calculateDesiredOrientation(target);
        
        // First adjust orientation if needed
        if (!adjustOrientation(desiredOrientation)) {
            return; // Still turning
        }
        
        // Move toward target
        double distance = sqrt(pow(target.x - position.x, 2) + pow(target.y - position.y, 2));
        double moveAmount = ROBOT_SPEED * dt;
        
        if (moveAmount >= distance) {
            // Reach the target point
            position = target;
            pathIndex++;
            
            if (pathIndex >= path.size()) {
                cout << "Robot reached the goal!\n";
                moving = false;
            }
        } else {
            // Move part way toward target
            if (abs(target.x - position.x) > 0)
                position.x += (target.x - position.x) / abs(target.x - position.x);
            if (abs(target.y - position.y) > 0)
                position.y += (target.y - position.y) / abs(target.y - position.y);
        }
    }
    
    // Get current position
    Point getPosition() const { return position; }
    
    // Get current path
    const vector<Point>& getPath() const { return path; }
    
    // Check if robot is moving
    bool isMoving() const { return moving; }
    
    // Get current orientation
    Orientation getOrientation() const { return orientation; }
};

// Simulation class
class RobotSimulation {
private:
    vector<vector<char>> map;
    AutonomousRobot robot;
    
    void printMap() {
        vector<vector<char>> displayMap = map;
        
        // Mark path
        for (const auto& p : robot.getPath()) {
            if (displayMap[p.y][p.x] == EMPTY) {
                displayMap[p.y][p.x] = PATH;
            }
        }
        
        // Mark robot position
        Point pos = robot.getPosition();
        char robotChar = 'R';
        switch(robot.getOrientation()) {
            case Orientation::NORTH: robotChar = '^'; break;
            case Orientation::EAST: robotChar = '>'; break;
            case Orientation::SOUTH: robotChar = 'v'; break;
            case Orientation::WEST: robotChar = '<'; break;
        }
        displayMap[pos.y][pos.x] = robotChar;
        
        // Print map
        cout << "\n";
        for (const auto& row : displayMap) {
            for (char cell : row) {
                cout << cell;
            }
            cout << "\n";
        }
        cout << "\n";
    }
    
public:
    RobotSimulation(const vector<vector<char>>& initialMap) : map(initialMap) {
        robot.initialize(map);
    }
    
    void run() {
        double dt = 1.0 / CONTROL_LOOP_HZ;
        int step = 0;
        
        while (robot.isMoving()) {
            cout << "Step " << step++ << ":\n";
            printMap();
            
            robot.update(dt);
            
            this_thread::sleep_for(chrono::milliseconds(static_cast<int>(dt * 1000)));
        }
        
        cout << "Final position:\n";
        printMap();
    }
};

int main() {
    // Define the map (20x10 grid)
    vector<vector<char>> simulationMap = {
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
        {'#','S','.','.','.','.','#','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','#','#','#','.','#','.','#','#','#','#','#','.','#','#','#','#','.','#'},
        {'#','.','#','.','.','.','#','.','.','.','.','.','#','.','.','.','.','#','.','#'},
        {'#','.','#','.','#','#','#','#','#','#','#','.','#','#','#','#','.','#','.','#'},
        {'#','.','#','.','.','.','.','.','.','.','#','.','.','.','.','.','.','#','.','#'},
        {'#','.','#','#','#','#','#','#','#','.','#','#','#','#','#','#','#','#','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','G','#'},
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
    };
    
    RobotSimulation sim(simulationMap);
    sim.run();
    
    return 0;
}