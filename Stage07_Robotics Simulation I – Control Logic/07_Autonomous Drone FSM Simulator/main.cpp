#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Grid size constants
const int WIDTH = 10;
const int HEIGHT = 10;
const int LEVELS = 3;

// FSM States
enum DroneState {
    SEARCHING,
    AVOIDING_OBSTACLE,
    LANDING,
    RETURNING_HOME
};

// Position in 3D grid
struct Position {
    int x, y, z;
};

// Simulated drone with basic sensors
struct Drone {
    Position pos;
    DroneState state;
    int battery; // 0 to 100
    Position target;
    Position home;
};

// Check if drone is at the target
bool atTarget(const Drone& drone) {
    return drone.pos.x == drone.target.x &&
           drone.pos.y == drone.target.y &&
           drone.pos.z == drone.target.z;
}

// Check for obstacle in front (simulate random obstacles)
bool isObstacleAhead() {
    return rand() % 5 == 0; // 20% chance
}

// Movement function
void moveForward(Drone& drone) {
    if (drone.pos.x + 1 < WIDTH) drone.pos.x++;
}

// Simulation tick: FSM transition + action
void simulateStep(Drone& drone) {
    switch (drone.state) {
        case SEARCHING:
            if (drone.battery < 20) {
                cout << "[FSM] Low battery. Returning home.\n";
                drone.state = RETURNING_HOME;
            } else if (isObstacleAhead()) {
                cout << "[FSM] Obstacle detected! Avoiding...\n";
                drone.state = AVOIDING_OBSTACLE;
            } else if (atTarget(drone)) {
                cout << "[FSM] Target reached. Landing...\n";
                drone.state = LANDING;
            } else {
                moveForward(drone);
                cout << "[ACTION] Moving forward to (" << drone.pos.x << ", " << drone.pos.y << ", " << drone.pos.z << ")\n";
            }
            break;

        case AVOIDING_OBSTACLE:
            drone.pos.y = (drone.pos.y + 1) % HEIGHT; // sidestep
            drone.state = SEARCHING;
            cout << "[ACTION] Sidestepping to avoid obstacle. Now at (" << drone.pos.x << ", " << drone.pos.y << ", " << drone.pos.z << ")\n";
            break;

        case RETURNING_HOME:
            if (drone.pos.x > drone.home.x) drone.pos.x--;
            else if (drone.pos.x < drone.home.x) drone.pos.x++;
            else if (drone.pos.y > drone.home.y) drone.pos.y--;
            else if (drone.pos.y < drone.home.y) drone.pos.y++;
            else if (drone.pos.z > drone.home.z) drone.pos.z--;
            else if (drone.pos.z < drone.home.z) drone.pos.z++;
            else drone.state = LANDING;
            cout << "[ACTION] Returning home. Position: (" << drone.pos.x << ", " << drone.pos.y << ", " << drone.pos.z << ")\n";
            break;

        case LANDING:
            cout << "[ACTION] Drone is landing...\n";
            break;
    }

    drone.battery -= 1;
}

int main() {
    srand(time(0));

    Drone drone = {
        {0, 0, 1}, // start position
        SEARCHING,
        100, // battery
        {7, 5, 1}, // target
        {0, 0, 1}  // home
    };

    cout << "=== Drone FSM Simulator Start ===\n";
    int steps = 0;
    while (drone.state != LANDING && drone.battery > 0 && steps < 50) {
        simulateStep(drone);
        steps++;
    }

    cout << "=== Simulation End ===\n";
    return 0;
}
