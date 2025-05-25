#include <iostream>
using namespace std;

// Base class for grid entities
class Entity {
protected:
    int x, y; // Position
public:
    Entity(int startX, int startY) : x(startX), y(startY) {}

    virtual void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    int getX() const { return x; }
    int getY() const { return y; }

    void printPosition(const string& name) const {
        cout << name << " Position: (" << x << ", " << y << ")" << endl;
    }
};

// Player class with direction-based movement
class Player : public Entity {
public:
    Player(int startX, int startY) : Entity(startX, startY) {}

    void handleInput(char input) {
        switch (tolower(input)) {
            case 'w': move(0, -1); break; // Up
            case 's': move(0, 1);  break; // Down
            case 'a': move(-1, 0); break; // Left
            case 'd': move(1, 0);  break; // Right
            default:
                cout << "Invalid input. Use W/A/S/D." << endl;
        }
    }
};

// Enemy chases the player
class Enemy : public Entity {
public:
    Enemy(int startX, int startY) : Entity(startX, startY) {}

    void chase(const Player& player) {
        if (x < player.getX()) move(1, 0);
        else if (x > player.getX()) move(-1, 0);

        if (y < player.getY()) move(0, 1);
        else if (y > player.getY()) move(0, -1);
    }
};

// Main game loop
int main() {
    Player player(0, 0);     // Starting at (0,0)
    Enemy enemy(5, 5);       // Enemy starts at (5,5)
    char input;

    cout << "Use W (up), A (left), S (down), D (right) to move. Q to quit." << endl;

    while (true) {
        // Show positions
        player.printPosition("Player");
        enemy.printPosition("Enemy");

        // End game if collision occurs
        if (player.getX() == enemy.getX() && player.getY() == enemy.getY()) {
            cout << "Game Over! Enemy caught the player!" << endl;
            break;
        }

        // Take user input
        cout << "Enter move: ";
        cin >> input;
        if (tolower(input) == 'q') {
            cout << "Game exited by user." << endl;
            break;
        }

        // Move player
        player.handleInput(input);

        // Enemy moves after player
        enemy.chase(player);
    }

    return 0;
}
