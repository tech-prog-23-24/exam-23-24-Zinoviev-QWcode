#include <iostream>
#include <string>
#include "SessionManager.h"

void printHelp() {
    std::cout << "Доступные команды:\n";
    std::cout << "  login          - Авторизация с логином и паролем\n";
    std::cout << "  logout         - Выход\n";
    std::cout << "  status         - Проверить активна ли сессия\n";
    std::cout << "  username       - Получить имя текущего пользователя\n";
    std::cout << "  set_timeout    - Установить timeout\n";
    std::cout << "  refresh        - Обновить сессию\n";
    std::cout << "  session_data   - Вывести информацию о текущей сессии\n";
    std::cout << "  help           - Вывести список команд\n";
    std::cout << "  exit           - Завершить программу\n";
}

int main() {
    setlocale(LC_ALL, "RU");

    SessionManager* session = SessionManager::getInstance();
    std::string command;

    std::cout << "МЕНЕДЖЕР СЕССИИ ПОЛЬЗОВАТЕЛЯ\n";
    std::cout << "Напишите help для вывода списка команд\n";

    while (true) {
        std::cout << "\nВведите команду: ";
        std::getline(std::cin, command);

        if (command == "help") {
            printHelp();
        }
        else if (command == "login") {
            std::string username, password;
            std::cout << "Введите имя пользователя: ";
            std::getline(std::cin, username);
            std::cout << "Введите пароль: ";
            std::getline(std::cin, password);

            if (session->login(username, password)) {
                std::cout << "Успешный вход\n";
            }
            else {
                std::cout << "Ошибка входа: неверный логин или пароль\n";
            }
        }
        else if (command == "logout") {
            session->logout();
            std::cout << "Выход\n";
        }
        else if (command == "status") {
            std::cout << "Сессия активна: " << (session->isLoggedIn() ? "Yes" : "No") << "\n";
        }
        else if (command == "username") {
            std::string username = session->getUsername();
            if (username.empty()) {
                std::cout << "Нет пользователей, прошедших авторизацию\n";
            }
            else {
                std::cout << "Текущий пользователь: " << username << "\n";
            }
        }
        else if (command == "set_timeout") {
            std::string input;
            std::cout << "Введите timeout: ";
            std::getline(std::cin, input);
            try {
                int timeout = std::stoi(input);
                session->setSessionTimeout(timeout);
                std::cout << "Timeout: " << timeout << " итераций\n";
            }
            catch (...) {
                std::cout << "Неверный ввод для timeout\n";
            }
        }
        else if (command == "refresh") {
            session->refreshSession();
            std::cout << "Сессия обновлена\n";
        }
        else if (command == "session_data") {
            std::cout << session->getSessionData() << "\n";
        }
        else if (command == "exit") {
            std::cout << "Завершение программы\n";
            break;
        }
        else {
            std::cout << "Неизвестная команда. Введите 'help' для просмотра списка команд\n";
        }
    }

    return 0;
}