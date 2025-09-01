#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include "ProfileManager.h"
#include "Models/Student.h"
#include "Models/Availability.h"
#include "utils/Color.h"

std::vector<std::string> ProfileManager::getCourses() {
    std::vector<std::string> courses;
    std::string course;

    std::cout << "Enter the your classes in the following format: <Dept. Code><Course Code> (ex. 'CPSC1060')\n";
    std::cout << "When you are done enter " << BOLD << "'done'" << RESET << "\n";
    std::cout << "If you wish to undo previous entry enter " << BOLD << "'undo'" << RESET << "\n";

    while (true) {
        std::cout << YELLOW << "Enter course: " << RESET;
        std::cin >> course;

        if (course == "done") break;
        if (course == "undo") {
            if (!courses.empty()) {
                std::cout << "Removed: " << courses.back() << "\n";
                courses.pop_back();
            } else {
                std::cout << "No course to undo.\n";
            }
            continue;
        }

        courses.push_back(course);
    }

    // Flush input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return courses;
}

std::vector<Availability> ProfileManager::getTimes() {
    std::vector<Availability> times;
    std::string day;
    int start, end;
    std::string input;

    std::cout << "Enter availability. Type 'undo' to remove the last, 'done' to finish:\n";

    // Loop getting times till user enters done
    while (true) {
        std::cout << YELLOW << "- Day " << "(e.g. Mon, Tue, Wed, Thr, Fri, Sat, Sun): " << RESET;
        std::getline(std::cin, input);

        if (input == "done") break;

        // Check if user wants to undo last course
        if (input == "undo") {
            if (!times.empty()) {
                auto last = times.back();
                std::cout << "   Removed: " << last.day << " " << last.startHour << "-" << last.endHour << "\n";
                times.pop_back();
            } else {
                std::cout << "   No availability to undo.\n";
            }
            continue;
        }

        day = input;
        if (day.empty()) continue;

        // Get time on day
        std::cout << "  " << YELLOW << "Start hour (24h format): " << RESET;
        std::cin >> start;
        std::cout << YELLOW << "  End hour (24h format): " << RESET;
        std::cin >> end;
        std::cin.ignore(); // flush newline for next getline

        // Check for valid ranges
        if (start < 0 || end > 24 || start >= end) {
            std::cout << "   Invalid time range. Try again.\n";
            continue;
        }

        times.push_back({day, start, end});
    }

    return times;
}

Student ProfileManager::createProfile() {
    std::cout << BOLD_BLUE << "+================+" << "\n";
    std::cout << "| Create Profile |" << "\n";
    std::cout << "+================+" << RESET << "\n";

    // Get unique id for profile
    std::ifstream idFileIn(ID_PATH);
    int currentID = 1000;

    // Check if there is data in id file
    if (idFileIn >> currentID)
        currentID++;
    idFileIn.close();

    // Write out id just created for this new user
    std::ofstream idFileOut(ID_PATH, std::ios::trunc);
    idFileOut << currentID;

    std::string id = std::to_string(currentID);

    // Get Student name
    std::string name;
    std::cout << YELLOW << "Name: " << RESET;
    std::getline(std::cin, name);
    std::cout << "\n";

    // Get current courses
    std::vector<std::string> courses = getCourses();

    std::cout << std::endl;

    // Get availability times
    std::vector<Availability> times = getTimes();

    // Show user profile created
    Student newStudent = {id, name, courses, times};
    std::cout << "\nYour New Profile:\n";
    std::cout << newStudent.toString() << "\n";
    std::cout << "*if you want to make changes to this now or in the future, choose the menu profile edit option\n";

    return newStudent;
}


void ProfileManager::editProfile(Student& student) {
    std::cout << BOLD_BLUE << "+==============+" << "\n";
    std::cout << "| Edit Profile |" << "\n";
    std::cout << "+==============+" << RESET << "\n";

    std::cout << "What would you like to edit?\n";
    std::cout << "1. Name\n";
    std::cout << "2. Enrolled Courses\n";
    std::cout << "3. Availability\n";
    std::cout << "4. All\n";
    std::cout << "5. Cancel\n";

    // Get what data the user whats to change
    int choice;
    std::cout << YELLOW << "Choice: " << RESET;
    std::cin >> choice;

    // flush input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << std::endl;

    switch (choice) {
        case 1: {
            std::string newName;
            std::cout << YELLOW << "Enter new name: " << RESET;
            std::getline(std::cin, newName);
            student.name = newName;
            std::cout << GREEN << "Name updated.\n" << RESET;
            break;
        }
        case 2: {
            student.courses = getCourses();
            std::cout << GREEN << "Courses updated.\n" << RESET;
            break;
        }
        case 3: {
            student.availability = getTimes();
            std::cout << GREEN << "Availability updated.\n" << RESET;
            break;
        }
        case 4: {
            std::string newName;
            std::cout << YELLOW << "Enter new name: " << RESET;
            std::getline(std::cin, newName);
            student.name = newName;
            student.courses = getCourses();
            student.availability = getTimes();
            std::cout << GREEN << "Profile fully updated.\n" << RESET;
            break;
        }
        case 5: {
            std::cout << CYAN << "Edit canceled.\n" << RESET;
            break;
        }
        default:
            std::cout << RED << "Invalid choice.\n" << RESET;
    }

    // Show updated profile
    std::cout << "\nYour Updated Profile:\n";
    std::cout << student.toString() << "\n";
}
