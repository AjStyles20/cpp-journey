#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include <cmath>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>
#include <stdexcept>

using namespace std;
using namespace std::chrono;

// ==================== CONSTANTS ====================
constexpr double BATTERY_DRAIN_RATE = 0.5;
constexpr double BATTERY_CHARGE_RATE = 2.0;
constexpr double LOW_BATTERY_THRESHOLD = 20.0;
constexpr double FULL_BATTERY = 100.0;
constexpr double EXPLORE_PROBABILITY = 0.3;
constexpr int STEP_DELAY_MS = 500;

// ==================== STRUCTURES ====================
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
class RobotState;

// ==================== WORLD MAP ====================
class WorldMap {
private:
    vector<vector<char>> grid;
    Point goal;
    Point chargingStation;
    int width, height;
    
    void initializeMap() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distX(0, width-1);
        uniform_int_distribution<int> distY(0, height-1);
        
        goal = {distX(gen), distY(gen)};
        grid[goal.y][goal.x] = 'G';
        
        chargingStation = {width/2, height/2};
        grid[chargingStation.y][chargingStation.x] = 'C';
        
        uniform_real_distribution<double> obstacleDist(0.0, 1.0);
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                Point current(x,y);
                if (obstacleDist(gen) < 0.2 && !(current == goal) && !(current == chargingStation)) {
                    grid[y][x] = '#';
                }
            }
        }
    }

public:
    WorldMap(int w, int h) : width(w), height(h), grid(h, vector<char>(w, '.')) {
        if (w <= 0 || h <= 0) {
            throw invalid_argument("Map dimensions must be positive");
        }
        initializeMap();
    }
    
    Point getChargingStation() const { return chargingStation; }
    Point getGoal() const { return goal; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    
    bool isGoalFound(const Point& pos) const { return pos == goal; }
    bool isAtChargingStation(const Point& pos) const { return pos == chargingStation; }
    bool isValidMove(const Point& pos) const {
        return pos.x >= 0 && pos.x < width && 
               pos.y >= 0 && pos.y < height && 
               grid[pos.y][pos.x] != '#';
    }
    
    void print(const Point& robotPos) const {
        vector<vector<char>> displayGrid = grid;
        
        if (robotPos.x >= 0 && robotPos.x < width && 
            robotPos.y >= 0 && robotPos.y < height) {
            displayGrid[robotPos.y][robotPos.x] = 'R';
        }
        
        cout << "\n";
        for (const auto& row : displayGrid) {
            for (char cell : row) {
                cout << cell << " ";
            }
            cout << "\n";
        }
    }
};

// ==================== ROBOT STATES ====================
class RobotState {
public:
    virtual ~RobotState() = default;
    virtual void execute(AutonomousRobot& robot) = 0;
    virtual string getName() const = 0;
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
    
    void clearPath() {
        currentPath.clear();
        pathIndex = 0;
    }

public:
    AutonomousRobot(int startX, int startY, int mapWidth, int mapHeight)
        : position(startX, startY), 
          batteryLevel(FULL_BATTERY),
          world(mapWidth, mapHeight),
          goalFound(false),
          pathIndex(0) {
              
        if (!world.isValidMove(position)) {
            throw runtime_error("Robot starting position is invalid");
        }
    }
    
    void setState(shared_ptr<RobotState> newState) {
        if (!newState) {
            throw invalid_argument("Cannot set null state");
        }
        cout << "State change: " << (currentState ? currentState->getName() : "None") 
             << " -> " << newState->getName() << "\n";
        currentState = newState;
        clearPath();
    }
    
    void drainBattery(double amount) { 
        if (amount < 0) {
            throw invalid_argument("Battery drain amount cannot be negative");
        }
        batteryLevel = max(0.0, batteryLevel - amount); 
    }
    
    void chargeBattery(double amount) { 
        if (amount < 0) {
            throw invalid_argument("Battery charge amount cannot be negative");
        }
        batteryLevel = min(FULL_BATTERY, batteryLevel + amount); 
    }
    
    double getBatteryLevel() const { return batteryLevel; }
    bool needsRecharge() const { return batteryLevel < LOW_BATTERY_THRESHOLD; }
    
    bool moveTo(const Point& newPos) {
        if (!world.isValidMove(newPos)) {
            cerr << "Error: Invalid move to (" << newPos.x << "," << newPos.y << ")\n";
            return false;
        }
        position = newPos;
        drainBattery(BATTERY_DRAIN_RATE);
        return true;
    }
    
    void setPath(const vector<Point>& path) {
        if (path.empty()) {
            throw invalid_argument("Path cannot be empty");
        }
        currentPath = path;
        pathIndex = 0;
    }
    
    bool followPath() {
        if (pathIndex >= currentPath.size()) {
            return false;
        }
        
        if (moveTo(currentPath[pathIndex])) {
            pathIndex++;
            return true;
        }
        return false;
    }
    
    bool checkForGoal() const { return world.isGoalFound(position); }
    bool checkForChargingStation() const { return world.isAtChargingStation(position); }
    
    const WorldMap& getWorld() const { return world; }
    Point getPosition() const { return position; }
    bool isGoalFound() const { return goalFound; }
    void setGoalFound(bool found) { goalFound = found; }
    
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
            return abs(a.x - b.x) + abs(a.y - b.y);
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
                
                if (!world.isValidMove(neighbor) || closedSet[neighbor.y][neighbor.x]) {
                    continue;
                }
                
                int g = current.g + 1;
                int h = heuristic(neighbor, target);
                openSet.emplace(neighbor, g, h, make_shared<Node>(current));
            }
        }
        
        return {};
    }
    
    void update() {
        if (!currentState) {
            throw runtime_error("Robot state not initialized");
        }
        
        cout << "\nBattery: " << batteryLevel << "% | ";
        currentState->execute(*this);
        world.print(position);
        this_thread::sleep_for(milliseconds(STEP_DELAY_MS));
    }
};

// ==================== CONCRETE STATE CLASSES ====================
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

// ==================== STATE IMPLEMENTATIONS ====================
void ExploreState::execute(AutonomousRobot& robot) {
    cout << "Exploring...";
    
    Point newPos = robot.getPosition();
    newPos.x += dist(gen);
    newPos.y += dist(gen);
    
    if (robot.moveTo(newPos)) {
        if (robot.checkForGoal()) {
            cout << "\nFound the goal while exploring!";
            robot.setGoalFound(true);
            robot.setState(make_shared<SeekGoalState>());
            return;
        }
        
        uniform_real_distribution<double> probDist(0.0, 1.0);
        if (probDist(gen) < EXPLORE_PROBABILITY) {
            cout << "\nLocated the goal in the distance!";
            robot.setState(make_shared<SeekGoalState>());
            return;
        }
    }
    
    if (robot.needsRecharge()) {
        cout << "\nBattery low, seeking charging station...";
        auto path = robot.findPathTo(robot.getWorld().getChargingStation());
        if (!path.empty()) {
            robot.setPath(path);
            robot.setState(make_shared<RechargeState>());
        }
    }
}

void SeekGoalState::execute(AutonomousRobot& robot) {
    cout << "Seeking goal...";
    
    if (robot.checkForGoal()) {
        cout << "\nGoal reached!";
        robot.setGoalFound(true);
        return;
    }
    
    auto path = robot.findPathTo(robot.getWorld().getGoal());
    if (path.empty()) {
        cout << "\nCan't find path to goal, switching to exploration";
        robot.setState(make_shared<ExploreState>());
        return;
    }
    
    if (!robot.followPath()) {
        cout << "\nPath blocked, replanning...";
        return;
    }
    
    if (robot.needsRecharge()) {
        cout << "\nBattery low, seeking charging station...";
        auto chargePath = robot.findPathTo(robot.getWorld().getChargingStation());
        if (!chargePath.empty()) {
            robot.setPath(chargePath);
            robot.setState(make_shared<RechargeState>());
        }
    }
}

void RechargeState::execute(AutonomousRobot& robot) {
    if (robot.checkForChargingStation()) {
        cout << "Charging...";
        robot.chargeBattery(BATTERY_CHARGE_RATE);
        
        if (robot.getBatteryLevel() >= FULL_BATTERY * 0.9) {
            cout << "\nBattery sufficiently charged";
            if (robot.isGoalFound()) {
                robot.setState(make_shared<SeekGoalState>());
            } else {
                robot.setState(make_shared<ExploreState>());
            }
        }
        return;
    }
    
    cout << "Moving to charging station...";
    if (!robot.followPath()) {
        cout << "\nPath blocked, replanning...";
        auto path = robot.findPathTo(robot.getWorld().getChargingStation());
        if (!path.empty()) {
            robot.setPath(path);
        } else {
            cout << "\nCannot reach charging station!";
        }
    }
}

// ==================== MAIN FUNCTION ====================
int main() {
    try {
        cout << "=== Autonomous Robot Simulator ===\n";
        cout << "Controls:\n";
        cout << "- R: Robot\n";
        cout << "- G: Goal\n";
        cout << "- C: Charging Station\n";
        cout << "- #: Obstacle\n\n";
        
        AutonomousRobot robot(1, 1, 20, 10);
        robot.setState(make_shared<ExploreState>());
        
        for (int i = 0; i < 100; i++) {
            cout << "\nStep " << i << ": ";
            robot.update();
            
            if (robot.isGoalFound() && robot.checkForGoal()) {
                cout << "\n=== MISSION ACCOMPLISHED ===\n";
                break;
            }
        }
    } 
    catch (const exception& e) {
        cerr << "\nERROR: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}