#pragma once
#include <string>

class SessionManager;

class SingletonDestroyer {
private:
    SessionManager* instance;
public:
    ~SingletonDestroyer();
    void initialize(SessionManager* p);
};

class SessionManager {
private:
    static SessionManager* instance;
    static SingletonDestroyer destroyer;

    std::string username;
    bool loggedIn;
    int timeoutCounter;
    int maxTimeout;

protected:
    SessionManager();
    ~SessionManager();
    SessionManager(const SessionManager&) = delete;
    SessionManager& operator=(const SessionManager&) = delete;
    friend class SingletonDestroyer;

public:
    static SessionManager* getInstance();
    bool login(const std::string& username, const std::string& password);
    void logout();
    bool isLoggedIn();
    std::string getUsername();
    void setSessionTimeout(int seconds);
    void refreshSession();
    std::string getSessionData();
};