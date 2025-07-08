#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <random>
#include <chrono>
#include <thread>
#include <queue>
#include <algorithm>

using namespace std;
using namespace std::chrono;

// Constants
const double BATTERY_DRAIN_RATE = 0.5;
const double BATTERY_CHARGE_RATE = 2.0;
const double LOW_BATTERY_THRESHOLD = 20.0;
const double FULL_BATTERY = 100.0;
const double EXPLORE_PROBABILITY = 0.3;

// 2D Point structure
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

// Environment map
class WorldMap {
private:
    vector<vector<char>> grid;
    Point goal;
    Point chargingStation;
    int width, height;
    
public:
    WorldMap(int w, int h) : width(w), height(h), grid(h, vector<char>(w, '.')) {
        // Place goal at random position
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distX(0, width-1);
        uniform_int_distribution<int> distY(0, height-1);
        
        goal = {distX(gen), distY(gen)};
        grid[goal.y][goal.x] = 'G';
        
        // Place charging station
        chargingStation = {width/2, height/2};
        grid[chargingStation.y][chargingStation.x] = 'C';
    }
    
    bool isGoalFound(const Point& pos) const { return pos == goal; }
    bool isAtChargingStation(const Point& pos) const { return pos == chargingStation; }
    
    bool isValidMove(const Point& pos) const {
        return pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height;
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
        cout << "\n";
    }
    
    Point getChargingStation() const { return chargingStation; }
    Point getGoal() const { return goal; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

// Abstract state class
class RobotState {
public:
    virtual void execute(class AutonomousRobot& robot) = 0;
    virtual string getName() const = 0;
    virtual ~RobotState() = default;
};

// Forward declaration of AutonomousRobot
class AutonomousRobot;

// Concrete state implementations
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

// Robot class with FSM
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
    
    // Pathfinding helper (simple BFS for demonstration)
    vector<Point> findPathTo(const Point& target) const {
        vector<vector<bool>> visited(world.getHeight(), vector<bool>(world.getWidth(), false));
        vector<vector<Point>> parent(world.getHeight(), vector<Point>(world.getWidth(), Point(-1, -1)));
        queue<Point> q;
        
        q.push(position);
        visited[position.y][position.x] = true;
        
        vector<Point> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        
        while (!q.empty()) {
            Point current = q.front();
            q.pop();
            
            if (current == target) {
                // Reconstruct path
                vector<Point> path;
                Point at = target;
                while (at.x != -1 && at.y != -1) {
                    path.push_back(at);
                    at = parent[at.y][at.x];
                }
                reverse(path.begin(), path.end());
                return path;
            }
            
            for (const auto& dir : directions) {
                Point neighbor(current.x + dir.x, current.y + dir.y);
                if (world.isValidMove(neighbor) && !visited[neighbor.y][neighbor.x]) {
                    visited[neighbor.y][neighbor.x] = true;
                    parent[neighbor.y][neighbor.x] = current;
                    q.push(neighbor);
                }
            }
        }
        
        return {}; // No path found
    }
};

// Implement state behaviors after AutonomousRobot is fully defined
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

int main() {
    AutonomousRobot robot(1, 1, 10, 10);
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