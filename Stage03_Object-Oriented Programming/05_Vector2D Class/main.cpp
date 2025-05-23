//Vector2D Class Definition
#include <iostream>

class Vector2D {
private:
    double x, y;

public:
    // Constructor
    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}

    // Member function for operator+ (vector addition)
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    // Friend function for operator<< (output)
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec);
};


std::ostream& operator<<(std::ostream& os, const Vector2D& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

int main() {
    Vector2D v1(1.0, 2.0);
    Vector2D v2(3.0, 4.0);

    // Using overloaded +
    Vector2D v3 = v1 + v2;

    // Using overloaded <<
    std::cout << "v1: " << v1 << "\n";
    std::cout << "v2: " << v2 << "\n";
    std::cout << "v1 + v2: " << v3 << "\n";

    return 0;
}