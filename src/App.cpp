#include "App.h"
#include "utils/Color.h"
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
        std::cout << BOLD << CYAN;
    std::cout << "===============================================\n";
    std::cout << "         Welcome to Study Buddy App!   \n";
    std::cout << " Helping you match with ideal study partners\n";
    std::cout << "===============================================\n\n";
    std::cout << RESET;

    std::cout << BOLD << GREEN << "Please select an option:\n\n" << RESET;

    std::cout << YELLOW << "  [1]  Create Your Profile\n" << RESET;
    std::cout << "      Get started by setting up your name, courses, and interests.\n\n";

    std::cout << YELLOW << "  [2]   View or Edit Your Profile\n" << RESET;
    std::cout << "      Review or update your details anytime.\n\n";

    std::cout << YELLOW << "  [3]  Manage Weekly Availability\n" << RESET;
    std::cout << "      Add or remove time slots when you're free to study.\n\n";

    std::cout << YELLOW << "  [4]  Search for Study Partners\n" << RESET;
    std::cout << "      Find classmates who share courses and time slots.\n\n";

    std::cout << YELLOW << "  [5]  View Suggested Matches\n" << RESET;
    std::cout << "      See who might be a good study buddy for you.\n\n";

    std::cout << YELLOW << "  [6]  Confirm a Study Session\n" << RESET;
    std::cout << "      Lock in a time with a partner and start learning.\n\n";

    std::cout << YELLOW << "  [7]  Exit the App\n" << RESET;
    std::cout << "      Save progress and return later.\n\n";

    std::cout << BOLD << CYAN;
    std::cout << "===============================================\n";
    std::cout << RESET;

    std::cout << BOLD << "Enter your choice [1-7]: " << RESET;
}

