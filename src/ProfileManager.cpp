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
        std::cout << YELLOW << "- Day " << "(e.g. Mon., Tue., Fri.): " << RESET;
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
    std::cout << BOLD_BLUE << "+==============+" << "\n";
    std::cout << "|Create Profile|" << "\n";
    std::cout << "+==============+" << RESET << "\n";

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
    Student newStudent = {name, id, courses, times};
    std::cout << "\nProfile Created:\n";
    std::cout << newStudent.toString() << "\n";
    std::cout << "*if you want to make changes to this now or in the future, choose the menu profile edit option\n";

    return newStudent;
}
