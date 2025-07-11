#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include <cmath>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>
#include <unordered_map>
#include <limits>

using namespace std;
using namespace std::chrono;

// ==================== CONSTANTS & STRUCTURES ====================
const double BATTERY_DRAIN_RATE = 0.5;
const double BATTERY_CHARGE_RATE = 2.0;
const double LOW_BATTERY_THRESHOLD = 20.0;
const double FULL_BATTERY = 100.0;
const double EXPLORE_PROBABILITY = 0.3;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    double distanceTo(const Point& other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
};

// Forward declarations
class AutonomousRobot;

// ==================== ROBOT STATE INTERFACE ====================
class RobotState {
public:
    virtual void execute(AutonomousRobot& robot) = 0;
    virtual string getName() const = 0;
    virtual ~RobotState() = default;
};

// ==================== WORLD MAP ====================
class WorldMap {
private:
    vector<vector<char>> grid;
    Point goal;
    Point chargingStation;
    int width, height;
    
public:
    WorldMap(int w, int h) : width(w), height(h), grid(h, vector<char>(w, '.')) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distX(0, width-1);
        uniform_int_distribution<int> distY(0, height-1);
        
        // Place goal
        goal = {distX(gen), distY(gen)};
        grid[goal.y][goal.x] = 'G';
        
        // Place charging station
        chargingStation = {width/2, height/2};
        grid[chargingStation.y][chargingStation.x] = 'C';
        
        // Add random obstacles (20% of cells)
        uniform_real_distribution<double> obstacleDist(0.0, 1.0);
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (obstacleDist(gen) < 0.2 && !(Point(x,y) == goal) && !(Point(x,y) == chargingStation)) {
                    grid[y][x] = '#';
                }
            }
        }
    }
    
    bool isGoalFound(const Point& pos) const { return pos == goal; }
    bool isAtChargingStation(const Point& pos) const { return pos == chargingStation; }
    bool isValidMove(const Point& pos) const {
        return pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height && grid[pos.y][pos.x] != '#';
    }
    
    void print(const Point& robotPos) const {
        vector<vector<char>> displayGrid = grid;
        displayGrid[robotPos.y][robotPos.x] = 'R';
        
        cout << "\n";
        for (const auto& row : displayGrid) {
            for (char cell : row) {
                cout << cell << " ";
            }
            cout << "\n";
        }
        cout << "Battery: " << (robotPos == chargingStation ? "Charging" : "Using") << "\n";
    }
    
    Point getChargingStation() const { return chargingStation; }
    Point getGoal() const { return goal; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

// ==================== ROBOT STATES ====================
class ExploreState : public RobotState {
private:
    random_device rd;
    mt19937 gen;
    uniform_int_distribution<int> dist;
    
public:
    ExploreState() : gen(rd()), dist(-1, 1) {}
    
    void execute(AutonomousRobot& robot) override;
    string getName() const override { return "Explore"; }
};

class SeekGoalState : public RobotState {
public:
    void execute(AutonomousRobot& robot) override;
    string getName() const override { return "SeekGoal"; }
};

class RechargeState : public RobotState {
public:
    void execute(AutonomousRobot& robot) override;
    string getName() const override { return "Recharge"; }
};

// ==================== AUTONOMOUS ROBOT ====================
class AutonomousRobot {
private:
    Point position;
    double batteryLevel;
    shared_ptr<RobotState> currentState;
    WorldMap world;
    bool goalFound;
    vector<Point> currentPath;
    size_t pathIndex;
    
public:
    AutonomousRobot(int startX, int startY, int mapWidth, int mapHeight)
        : position(startX, startY), batteryLevel(FULL_BATTERY), 
          world(mapWidth, mapHeight), goalFound(false), pathIndex(0) {}
    
    // State management
    void setState(shared_ptr<RobotState> newState) {
        cout << "State change: " << (currentState ? currentState->getName() : "None") 
             << " -> " << newState->getName() << "\n";
        currentState = newState;
    }
    
    shared_ptr<RobotState> getCurrentState() const {
        return currentState;
    }
    
    // Battery management
    void drainBattery(double amount) { 
        batteryLevel = max(0.0, batteryLevel - amount); 
    }
    void chargeBattery(double amount) { 
        batteryLevel = min(FULL_BATTERY, batteryLevel + amount); 
    }
    double getBatteryLevel() const { return batteryLevel; }
    bool needsRecharge() const { return batteryLevel < LOW_BATTERY_THRESHOLD; }
    
    // Movement
    bool moveTo(const Point& newPos) {
        if (world.isValidMove(newPos)) {
            position = newPos;
            drainBattery(BATTERY_DRAIN_RATE);
            return true;
        }
        return false;
    }
    
    // Navigation
    void setPath(const vector<Point>& path) {
        currentPath = path;
        pathIndex = 0;
    }
    
    bool followPath() {
        if (pathIndex >= currentPath.size()) return false;
        
        if (moveTo(currentPath[pathIndex])) {
            pathIndex++;
            return true;
        }
        return false;
    }
    
    // Sensors
    bool checkForGoal() const { return world.isGoalFound(position); }
    bool checkForChargingStation() const { return world.isAtChargingStation(position); }
    
    // World interaction
    const WorldMap& getWorld() const { return world; }
    Point getPosition() const { return position; }
    bool isGoalFound() const { return goalFound; }
    void setGoalFound(bool found) { goalFound = found; }
    
    // Main update loop
    void update() {
        currentState->execute(*this);
        world.print(position);
        this_thread::sleep_for(milliseconds(500));
    }
    
    // Pathfinding (A* algorithm)
    vector<Point> findPathTo(const Point& target) const {
        struct Node {
            Point point;
            int g, h, f;
            shared_ptr<Node> parent;
            
            Node(Point p, int g, int h, shared_ptr<Node> parent = nullptr)
                : point(p), g(g), h(h), f(g+h), parent(parent) {}
            
            bool operator>(const Node& other) const { return f > other.f; }
        };
        
        auto heuristic = [](Point a, Point b) {
            return abs(a.x - b.x) + abs(a.y - b.y); // Manhattan distance
        };
        
        priority_queue<Node, vector<Node>, greater<Node>> openSet;
        vector<vector<bool>> closedSet(world.getHeight(), vector<bool>(world.getWidth(), false));
        
        openSet.emplace(position, 0, heuristic(position, target));
        
        while (!openSet.empty()) {
            Node current = openSet.top();
            openSet.pop();
            
            if (current.point == target) {
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
            
            vector<Point> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};
            for (const auto& dir : directions) {
                Point neighbor(current.point.x + dir.x, current.point.y + dir.y);
                
                if (!world.isValidMove(neighbor) || closedSet[neighbor.y][neighbor.x]) 
                    continue;
                
                int g = current.g + 1;
                int h = heuristic(neighbor, target);
                openSet.emplace(neighbor, g, h, make_shared<Node>(current));
            }
        }
        
        return {}; // No path found
    }
};

// ==================== STATE IMPLEMENTATIONS ====================
void ExploreState::execute(AutonomousRobot& robot) {
    cout << "Exploring... (Battery: " << robot.getBatteryLevel() << "%)\n";
    
    // Random movement
    Point newPos = robot.getPosition();
    newPos.x += dist(gen);
    newPos.y += dist(gen);
    
    if (robot.moveTo(newPos)) {
        // Check if we found the goal by chance
        if (robot.checkForGoal()) {
            cout << "Found the goal while exploring!\n";
            robot.setGoalFound(true);
            robot.setState(make_shared<SeekGoalState>());
            return;
        }
        
        // Random chance to find the goal
        uniform_real_distribution<double> probDist(0.0, 1.0);
        if (probDist(gen) < EXPLORE_PROBABILITY) {
            cout << "Located the goal in the distance!\n";
            robot.setState(make_shared<SeekGoalState>());
            return;
        }
    }
    
    // Check battery level
    if (robot.needsRecharge()) {
        cout << "Battery low, seeking charging station...\n";
        auto path = robot.findPathTo(robot.getWorld().getChargingStation());
        if (!path.empty()) {
            robot.setPath(path);
            robot.setState(make_shared<RechargeState>());
        }
    }
}

void SeekGoalState::execute(AutonomousRobot& robot) {
    if (robot.checkForGoal()) {
        cout << "Goal reached!\n";
        robot.setGoalFound(true);
        return;
    }
    
    cout << "Seeking goal... (Battery: " << robot.getBatteryLevel() << "%)\n";
    
    // Find path to goal
    auto path = robot.findPathTo(robot.getWorld().getGoal());
    if (path.empty()) {
        cout << "Can't find path to goal, switching to exploration\n";
        robot.setState(make_shared<ExploreState>());
        return;
    }
    
    // Follow path
    if (!robot.followPath()) {
        cout << "Path following failed, replanning...\n";
        return;
    }
    
    // Check battery level
    if (robot.needsRecharge()) {
        cout << "Battery low, seeking charging station...\n";
        auto chargePath = robot.findPathTo(robot.getWorld().getChargingStation());
        if (!chargePath.empty()) {
            robot.setPath(chargePath);
            robot.setState(make_shared<RechargeState>());
        }
    }
}

void RechargeState::execute(AutonomousRobot& robot) {
    if (robot.checkForChargingStation()) {
        cout << "Charging... (Battery: " << robot.getBatteryLevel() << "%)\n";
        robot.chargeBattery(BATTERY_CHARGE_RATE);
        
        if (robot.getBatteryLevel() >= FULL_BATTERY * 0.9) {
            cout << "Battery sufficiently charged.\n";
            if (robot.isGoalFound()) {
                robot.setState(make_shared<SeekGoalState>());
            } else {
                robot.setState(make_shared<ExploreState>());
            }
        }
        return;
    }
    
    cout << "Moving to charging station... (Battery: " << robot.getBatteryLevel() << "%)\n";
    
    if (!robot.followPath()) {
        cout << "Path to charging station blocked, replanning...\n";
        auto path = robot.findPathTo(robot.getWorld().getChargingStation());
        if (!path.empty()) {
            robot.setPath(path);
        } else {
            cout << "Cannot reach charging station!\n";
        }
    }
}

// ==================== MAIN FUNCTION ====================
int main() {
    AutonomousRobot robot(1, 1, 20, 10);
    robot.setState(make_shared<ExploreState>());
    
    for (int i = 0; i < 100; i++) {
        cout << "\nStep " << i << ": ";
        robot.update();
        
        if (robot.isGoalFound() && robot.checkForGoal()) {
            cout << "Mission accomplished!\n";
            break;
        }
    }
    
    return 0;
}