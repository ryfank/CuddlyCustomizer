#include "loginManager.h"
#include <functional> // For std::hash

LoginManager::LoginManager() {
    // Add a default user for testing
    addUser("test", "1234");
}

bool LoginManager::verifyCredentials(const std::string& username, const std::string& password) {
    std::string hashed = hashPassword(password);
    auto it = credentials.find(username);
    return it != credentials.end() && it->second == hashed;
}

void LoginManager::addUser(const std::string& username, const std::string& password) {
    credentials[username] = hashPassword(password);
}

// Simple hash placeholder (replace with real hash like Argon2 or SHA256 later)
std::string LoginManager::hashPassword(const std::string& password) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(password));
}

