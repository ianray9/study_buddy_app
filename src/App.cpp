#include "App.h"
#include <iostream>

void App::initialize() {
    std::cout << "Initializing Study Buddy App..." << std::endl;
}

void App::run() {
    bool running = true;
    while (running) {
        displayMenu();

        int choice;
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Create or login to profile (stub)." << std::endl;
                break;
            case 2:
                std::cout << "Exit selected." << std::endl;
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
                break;
        }
    }
}

void App::displayMenu() {
    std::cout << "\n--- Study Buddy Menu ---\n";
    std::cout << "1. Create/Login Profile\n";
    std::cout << "2. Exit\n";
}

