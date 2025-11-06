#ifndef LOGIN_MANAGER_H
#define LOGIN_MANAGER_H

#include <string>
#include <unordered_map>

class LoginManager {
public:
    LoginManager();

    bool verifyCredentials(const std::string& username, const std::string& password);
    void addUser(const std::string& username, const std::string& password);

private:
    std::unordered_map<std::string, std::string> credentials;

    std::string hashPassword(const std::string& password);
};

#endif