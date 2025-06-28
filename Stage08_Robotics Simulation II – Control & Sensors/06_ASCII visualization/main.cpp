#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
#include <thread>
#include <random>
#include <iomanip>

using namespace std;

// Constants
const int MAP_SIZE = 20;
const double MAX_SPEED = 2.0;
const double SAFE_DISTANCE = 2.0;
const double ARRIVAL_THRESHOLD = 0.5;
const double CONTROL_LOOP_HZ = 5.0;

// 2D Point structure
struct Point {
    double x, y;
    
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    double distanceTo(const Point& other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
    
    Point toMapCoords() const {
        return Point(round(x), round(y));
    }
};

// ASCII Map Visualization
class MapVisualizer {
private:
    vector<vector<char>> grid;
    Point beacon;
    
public:
    MapVisualizer() : grid(MAP_SIZE, vector<char>(MAP_SIZE, '.')) {}
    
    void update(const Point& robot, const Point& beacon, const vector<Point>& obstacles) {
        // Clear the grid
        for (auto& row : grid) {
            fill(row.begin(), row.end(), '.');
        }
        
        // Mark obstacles
        for (const auto& obs : obstacles) {
            Point mapObs = obs.toMapCoords();
            if (inBounds(mapObs)) {
                grid[mapObs.y][mapObs.x] = 'X';
            }
        }
        
        // Mark beacon
        Point mapBeacon = beacon.toMapCoords();
        if (inBounds(mapBeacon)) {
            grid[mapBeacon.y][mapBeacon.x] = 'B';
        }
        
        // Mark robot
        Point mapRobot = robot.toMapCoords();
        if (inBounds(mapRobot)) {
            grid[mapRobot.y][mapRobot.x] = 'R';
        }
    }
    
    void draw() const {
        cout << "\n  ";
        for (int x = 0; x < MAP_SIZE; x++) cout << setw(2) << x;
        cout << "\n";
        
        for (int y = 0; y < MAP_SIZE; y++) {
            cout << setw(2) << y << " ";
            for (int x = 0; x < MAP_SIZE; x++) {
                cout << grid[y][x] << " ";
            }
            cout << "\n";
        }
        cout << "\nLegend: R=Robot, B=Beacon, X=Obstacle\n";
    }
    
private:
    bool inBounds(const Point& p) const {
        return p.x >= 0 && p.x < MAP_SIZE && p.y >= 0 && p.y < MAP_SIZE;
    }
};

// Sensor and Controller implementations would go here...
// (Same as previous implementation but with adjusted obstacle positions)

int main() {
    Point start(1, 1);
    Point beacon(15, 15);
    
    // Fixed obstacles for better visualization
    vector<Point> obstacles = {
        Point(5, 5), Point(5, 6), Point(5, 7),
        Point(10, 10), Point(10, 11), Point(10, 12),
        Point(8, 15), Point(9, 15), Point(10, 15)
    };
    
    // Initialize visualization
    MapVisualizer visualizer;
    Point robotPos = start;
    
    // Simulate navigation loop
    double dt = 1.0 / CONTROL_LOOP_HZ;
    int step = 0;
    
    while (robotPos.distanceTo(beacon) > ARRIVAL_THRESHOLD) {
        // Clear screen (works on most terminals)
        cout << "\033[2J\033[1;1H";
        
        // Update visualization
        visualizer.update(robotPos, beacon, obstacles);
        visualizer.draw();
        
        // Simple navigation logic (replace with your controller)
        Point direction(beacon.x - robotPos.x, beacon.y - robotPos.y);
        double dist = robotPos.distanceTo(beacon);
        if (dist > 0) {
            direction.x /= dist;
            direction.y /= dist;
        }
        
        // Simple obstacle avoidance
        for (const auto& obs : obstacles) {
            if (robotPos.distanceTo(obs) < SAFE_DISTANCE) {
                Point avoid(robotPos.x - obs.x, robotPos.y - obs.y);
                double avoidDist = robotPos.distanceTo(obs);
                if (avoidDist > 0) {
                    avoid.x /= avoidDist;
                    avoid.y /= avoidDist;
                }
                direction.x += avoid.x * 0.5;
                direction.y += avoid.y * 0.5;
            }
        }
        
        // Normalize and apply speed
        double dirLen = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (dirLen > 0) {
            direction.x /= dirLen;
            direction.y /= dirLen;
        }
        
        // Update position
        robotPos.x += direction.x * MAX_SPEED * dt;
        robotPos.y += direction.y * MAX_SPEED * dt;
        
        // Display info
        cout << "Step: " << step++ << "\n";
        cout << "Position: (" << fixed << setprecision(1) << robotPos.x 
             << ", " << robotPos.y << ")\n";
        cout << "Distance to beacon: " << robotPos.distanceTo(beacon) << "\n";
        
        // Control loop timing
        this_thread::sleep_for(chrono::milliseconds(static_cast<int>(dt * 1000)));
    }
    
    cout << "\nMission complete! Robot reached the beacon!\n";
    return 0;
}