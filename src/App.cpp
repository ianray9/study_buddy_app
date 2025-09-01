#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>
#include <filesystem>
#include <vector>
#include "App.h"
#include "utils/Color.h"

void App::initialize() {
    std::cout << "Initializing Study Buddy App...\n";
    ensureDataFilesExist();

    // Load students and sessions from files
    students = fileHandler.loadProfiles();
    sessions = fileHandler.loadSessions();


    std::cout << "Loaded " << students.size() << " student profiles.\n";
    std::cout << "Loaded " << sessions.size() << " scheduled sessions.\n";
}

void App::run() {
    bool running = true;

    while (running) {
        displayMenu();

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush newline

        switch (choice) {
            case 1:
                handleCreateOrLogin();
                break;
            case 2:
                handleEditProfile();
                break;
            case 3:
                handleSearchPartners();
                break;
            case 4:
                handleSuggestedSessions();
                break;
            case 5:
                handleConfirmSession();
                break;
            case 6:
                std::cout << "Exiting app and saving data...\n";
                saveData();
                running = false;
                break;
            default:
                std::cout << RED << "Invalid choice. Please enter a number between 1 and 6.\n" << RESET;
                break;
        }

        std::cout << "\n"; // spacing between operations
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

    std::cout << YELLOW << "  [1]  Create or Login Your Profile\n" << RESET;
    std::cout << "      Get started by setting up your name, courses, and interests.\n\n";

    std::cout << YELLOW << "  [2]  View or Edit Your Profile\n" << RESET;
    std::cout << "      Review or update your details anytime.\n\n";

    std::cout << YELLOW << "  [3]  Search for Study Partners\n" << RESET;
    std::cout << "      Find classmates who share courses and time slots.\n\n";

    std::cout << YELLOW << "  [4]  View Suggested Matches\n" << RESET;
    std::cout << "      See who might be a good study buddy for you.\n\n";

    std::cout << YELLOW << "  [5]  Confirm a Study Session\n" << RESET;
    std::cout << "      Lock in a time with a partner and start learning.\n\n";

    std::cout << YELLOW << "  [6]  Exit the App\n" << RESET;
    std::cout << "      Save progress and return later.\n\n";

    std::cout << BOLD << CYAN;
    std::cout << "===============================================\n";
    std::cout << RESET;

    std::cout << BOLD << "Enter your choice [1-6]: " << RESET;
}

void App::handleCreateOrLogin() {
    if (currentStudent != nullptr) {
        std::cout << CYAN << "You are already logged in as " << currentStudent->name << ".\n";
        std::cout << "If you want to switch accounts, please log out first.\n" << RESET;
        return;
    }

    std::cout << BOLD_BLUE << "+========================+" << "\n";
    std::cout << "| Create Profile / Login |" << "\n";
    std::cout << "+========================+" << RESET << "\n\n";

    std::cout << "Do you want to:\n";
    std::cout << "  [1] Create a new profile\n";
    std::cout << "  [2] Login with existing profile\n";
    std::cout << "Choice: ";
    int choice;
    std::cin >> choice;

    // flush newline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 1) {
        Student newStudent = profileManager.createProfile();

        // Check if ID is unique
        auto it = std::find_if(students.begin(), students.end(),
                               [&newStudent](const Student& s) { return s.id == newStudent.id; });
        if (it == students.end()) {
            students.push_back(newStudent);
            currentStudent = &students.back();
            std::cout << GREEN << "Profile created and logged in as " << currentStudent->name << ".\n" << RESET;
        } else {
            std::cout << RED << "Error: A profile with this ID already exists.\n" << RESET;
        }

    } else if (choice == 2) {
        if (students.empty()) {
            std::cout << RED << "No profiles exist yet. Please create one first.\n" << RESET;
            return;
        }
        std::cout << "Enter your student ID: ";
        std::string id;
        std::getline(std::cin, id);

        auto it = std::find_if(students.begin(), students.end(),
                               [&id](const Student& s) { return s.id == id; });
        if (it != students.end()) {
            currentStudent = &(*it);
            std::cout << GREEN << "Logged in as " << currentStudent->name << ".\n" << RESET;
        } else {
            std::cout << RED << "No student found with ID " << id << ".\n" << RESET;
        }
    } else {
        std::cout << RED << "Invalid choice.\n" << RESET;
    }
}

void App::handleEditProfile() {
    if (currentStudent == nullptr) {
        std::cout << RED << "You must be logged in to edit your profile.\n" << RESET;
        return;
    }

    profileManager.editProfile(*currentStudent);

    std::cout << CYAN << "\nProfile updated successfully.\n";
    std::cout << currentStudent->toString() << "\n" << RESET;
}

void App::handleSearchPartners() {
    if (currentStudent == nullptr) {
        std::cout << RED << "You must be logged in to search for partners.\n" << RESET;
        return;
    }

    std::vector<Student> matches = partnerMatcher.findMatchingStudents(*currentStudent, students);

    if (matches.empty()) {
        std::cout << RED << "No study partners found matching your courses and availability.\n" << RESET;
        return;
    }

    std::cout << GREEN << "Found " << matches.size() << " potential study partner(s):\n" << RESET;
    for (const Student& match : matches) {
        std::cout << "  - " << match.name << " (" << match.id << ")\n";
    }
}

void App::handleConfirmSession() {
    if (!currentStudent) {
        std::cout << RED << "Please log in or create a profile first.\n" << RESET;
        return;
    }

    std::vector<Student> matches = partnerMatcher.findMatchingStudents(*currentStudent, students);
    if (matches.empty()) {
        std::cout << RED << "No matching students found.\n" << RESET;
        return;
    }

    std::cout << BOLD_BLUE << "Matched Students:\n" << RESET;
    for (size_t i = 0; i < matches.size(); ++i) {
        std::cout << "  [" << i + 1 << "] " << matches[i].name << "\n";
    }

    std::cout << YELLOW << "Select a student by number: " << RESET;
    int index;
    std::cin >> index;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (index < 1 || index > static_cast<int>(matches.size())) {
        std::cout << RED << "Invalid selection.\n" << RESET;
        return;
    }

    const Student& partner = matches[index - 1];

    std::string sharedCourse;
    for (std::string course : currentStudent->courses) {
        if (std::find(partner.courses.begin(), partner.courses.end(), course) != partner.courses.end()) {
            sharedCourse = course;
            break;
        }
    }

    if (sharedCourse.empty()) {
        std::cout << RED << "No shared course found.\n" << RESET;
        return;
    }

    Availability sharedTime;
    bool foundTime = false;

    for (Availability a1 : currentStudent->availability) {
        for (Availability a2 : partner.availability) {
            if (a1.day == a2.day && a1.overlapsWith(a2)) {
                sharedTime = {
                    a1.day,
                    std::max(a1.startHour, a2.startHour),
                    std::min(a1.endHour, a2.endHour)
                };
                foundTime = true;
                break;
            }
        }
        if (foundTime) break;
    }

    if (!foundTime) {
        std::cout << RED << "No overlapping availability.\n" << RESET;
        return;
    }

    Session newSession = sessionScheduler.confirmSession(
        *currentStudent, partner, sharedCourse, sharedTime
    );

    sessions.push_back(newSession);

    std::cout << GREEN << "\nConfirmed Session:\n" << RESET;
    std::cout << newSession.toString() << "\n";
}

void App::handleSuggestedSessions() {
    if (!currentStudent) {
        std::cout << RED << "Please log in or create a profile first.\n" << RESET;
        return;
    }

    std::vector<Student> matches = partnerMatcher.findMatchingStudents(*currentStudent, students);
    if (matches.empty()) {
        std::cout << RED << "No matching students found.\n" << RESET;
        return;
    }

    std::vector<Session> suggestions = sessionScheduler.suggestSessions(*currentStudent, matches);

    if (suggestions.empty()) {
        std::cout << RED << "No suggested sessions at this time.\n" << RESET;
        return;
    }

    std::cout << BOLD_BLUE << "\nSuggested Sessions for " << currentStudent->name << ":\n\n" << RESET;

    for (Session session : suggestions) {
        std::cout << session.toString() << "\n";
    }
}

void App::saveData() {
    fileHandler.saveProfiles(students);
    fileHandler.saveSessions(sessions);
    std::cout << GREEN << "All data saved successfully.\n" << RESET;
}

// Call this during initialize before loading files
void App::ensureDataFilesExist() {
    namespace fs = std::filesystem;

    struct FileHeader {
        std::string path;
        std::string headerLine;
    };

    std::vector<FileHeader> filesToCheck = {
        {"data/profiles.txt", "Name,StudentID,Courses,Availability\n"},
        {"data/sessions.txt", "SessionID,Students,Course,Time\n"},
        {"data/currentID.txt", "0\n"}  // If currentID.txt is just a number
    };

    for (FileHeader file : filesToCheck) {
        if (!fs::exists(file.path) || fs::is_empty(file.path)) {
            std::ofstream outFile(file.path);

            outFile << file.headerLine;
            std::cout << "Created data file with header: " << file.path << std::endl;
        }
    }
}

