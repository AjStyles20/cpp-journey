#include "library.h"
#include <iostream>
#include <vector>

namespace Library {

// Static vector to store the registered users (local to this file)
static std::vector<User> users;

void registerUser(const User& user) {
    int userId = user.userId;
    std::string name = user.name;

    users.push_back(user);
    std::cout << "User '" << name << "' with ID " << userId << " registered." << std::endl;
}

void displayUsers() {
    if (users.empty()) {
        std::cout << "No users registered in the library." << std::endl;
        return;
    }
    std::cout << "\n--- Registered Users ---" << std::endl;
    for (const auto& user : users) {
        std::cout << "User ID: " << user.userId << std::endl;
        std::cout << "Name: " << user.name << std::endl;
        std::cout << "----------------------" << std::endl;
    }
}

} // namespace Library