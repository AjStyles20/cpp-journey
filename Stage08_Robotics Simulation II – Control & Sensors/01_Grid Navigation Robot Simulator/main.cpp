
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std;

// Grid cell types
enum class CellType {
    EMPTY,
    ROBOT,
    GOAL,
    OBSTACLE,
    PATH
};

// Direction vectors (up, down, left, right)
const vector<pair<int, int>> DIRECTIONS = {{-1,0}, {1,0}, {0,-1}, {0,1}};

class GridNavigator {
private:
    vector<vector<CellType>> grid;
    int rows, cols;
    pair<int, int> robotPos;
    pair<int, int> goalPos;
    mt19937 rng;

    // Check if position is valid and accessible
    bool isValidPosition(int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols && 
               grid[x][y] != CellType::OBSTACLE;
    }

    // Simple heuristic: Manhattan distance to goal
    int distanceToGoal(int x, int y) const {
        return abs(x - goalPos.first) + abs(y - goalPos.second);
    }

public:
    GridNavigator(int r, int c) : rows(r), cols(c), grid(r, vector<CellType>(c, CellType::EMPTY)) {
        rng.seed(random_device()());
        
        // Place robot at random edge position
        uniform_int_distribution<int> edgeDist(0, 2*(rows+cols)-1);
        int edge = edgeDist(rng);
        
        if (edge < rows) { // Top edge
            robotPos = {0, edge};
        } else if (edge < rows + cols) { // Right edge
            robotPos = {edge - rows, cols - 1};
        } else if (edge < 2*rows + cols) { // Bottom edge
            robotPos = {rows - 1, (2*rows + cols - 1) - edge};
        } else { // Left edge
            robotPos = {(2*(rows+cols) - 1) - edge, 0};
        }
        grid[robotPos.first][robotPos.second] = CellType::ROBOT;

        // Place goal at center
        goalPos = {rows/2, cols/2};
        grid[goalPos.first][goalPos.second] = CellType::GOAL;

        // Add random obstacles (20% of cells)
        uniform_int_distribution<int> obstacleDist(0, 4);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == CellType::EMPTY && obstacleDist(rng) == 0) {
                    grid[i][j] = CellType::OBSTACLE;
                }
            }
        }
    }

    // Try to move toward goal, with random movement if stuck
    void moveRobot() {
        vector<pair<int, int>> possibleMoves;
        int currentDist = distanceToGoal(robotPos.first, robotPos.second);

        // Find all valid moves that get us closer to goal
        for (auto [dx, dy] : DIRECTIONS) {
            int nx = robotPos.first + dx;
            int ny = robotPos.second + dy;
            if (isValidPosition(nx, ny) && distanceToGoal(nx, ny) < currentDist) {
                possibleMoves.emplace_back(nx, ny);
            }
        }

        // If no progress possible, consider all valid moves
        if (possibleMoves.empty()) {
            for (auto [dx, dy] : DIRECTIONS) {
                int nx = robotPos.first + dx;
                int ny = robotPos.second + dy;
                if (isValidPosition(nx, ny)) {
                    possibleMoves.emplace_back(nx, ny);
                }
            }
        }

        // If still no moves, we're stuck (shouldn't happen with edge start)
        if (possibleMoves.empty()) return;

        // Choose random move from available options
        uniform_int_distribution<int> moveDist(0, possibleMoves.size()-1);
        auto [newX, newY] = possibleMoves[moveDist(rng)];

        // Update grid
        grid[robotPos.first][robotPos.second] = CellType::PATH;
        robotPos = {newX, newY};
        grid[robotPos.first][robotPos.second] = CellType::ROBOT;
    }

    // Check if robot has reached goal
    bool goalReached() const {
        return robotPos == goalPos;
    }

    // Display the grid
    void display() const {
        cout << "\033[2J\033[1;1H"; // Clear screen
        cout << "Grid Navigation Simulation (Ctrl+C to exit)\n";
        cout << "Legend: R=Robot, G=Goal, #=Obstacle, .=Path\n\n";

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                switch (grid[i][j]) {
                    case CellType::ROBOT: cout << "R"; break;
                    case CellType::GOAL: cout << "G"; break;
                    case CellType::OBSTACLE: cout << "#"; break;
                    case CellType::PATH: cout << "."; break;
                    default: cout << " "; break;
                }
                cout << " ";
            }
            cout << "\n";
        }
        cout << "\nDistance to goal: " << distanceToGoal(robotPos.first, robotPos.second) << "\n";
    }
};

int main() {
    const int ROWS = 15;
    const int COLS = 30;

    GridNavigator navigator(ROWS, COLS);
    navigator.display();

    while (!navigator.goalReached()) {
        this_thread::sleep_for(chrono::milliseconds(200)); // 0.2s delay
        navigator.moveRobot();
        navigator.display();
    }

    cout << "\nGoal reached!\n";
    return 0;
}