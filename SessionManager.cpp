#include "SessionManager.h"

SingletonDestroyer::~SingletonDestroyer() {
    delete instance;
}

void SingletonDestroyer::initialize(SessionManager* p) {
    instance = p;
}

SessionManager* SessionManager::instance = nullptr;
SingletonDestroyer SessionManager::destroyer;

SessionManager::SessionManager() : loggedIn(false), timeoutCounter(0), maxTimeout(5) {}

SessionManager::~SessionManager() {}

SessionManager* SessionManager::getInstance() {
    if (!instance) {
        instance = new SessionManager();
        destroyer.initialize(instance);
    }
    return instance;
}

bool SessionManager::login(const std::string& username, const std::string& password) {
    if (!loggedIn && !username.empty() && password == "password") {
        this->username = username;
        loggedIn = true;
        timeoutCounter = 0;
        return true;
    }
    return false;
}

void SessionManager::logout() {
    loggedIn = false;
    username.clear();
    timeoutCounter = 0;
}

bool SessionManager::isLoggedIn() {
    if (!loggedIn) return false;
    if (timeoutCounter >= maxTimeout) {
        logout();
        return false;
    }
    timeoutCounter++;
    return true;
}

std::string SessionManager::getUsername() {
    return username;
}

void SessionManager::setSessionTimeout(int seconds) {
    if (seconds > 0) {
        maxTimeout = seconds;
    }
}

void SessionManager::refreshSession() {
    if (loggedIn) {
        timeoutCounter = 0;
    }
}

std::string SessionManager::getSessionData() {
    if (!isLoggedIn()) {
        return "Нет активной сессии";
    }
    return "Пользователь: " + username + "\nTimeout: " +
        std::to_string(maxTimeout) + " итераций\nОсталось: " +
        std::to_string(maxTimeout - timeoutCounter) + " итераций";
}