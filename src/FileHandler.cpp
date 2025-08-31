#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "FileHandler.h"
#include "Models/Student.h"
#include "Models/Availability.h"
#include "Models/Session.h"
#include "third_party/csv.hpp"

// Helper Funciton to split list into tokens
std::vector<std::string> splitList(const std::string& in, char delim) {
    std::vector<std::string> tokens;
    std::stringstream csvList;
    csvList << in;

    std::string entry;
    while (std::getline(csvList, entry, delim))
        tokens.push_back(entry);

    return tokens;
}

std::vector<Session> FileHandler::loadSessions() {
    std::vector<Session> sessions;
    csv::CSVReader reader(AVAILABILITY_PATH, csv::CSVFormat().header_row(0));

    for (csv::CSVRow& row : reader) {
        // Get data from csv style rows
        std::string id = row["SessionID"].get<>();
        std::string namesStr = row["Students"].get<>();
        std::string course = row["Course"].get<>();
        std::string availabilityStr = row["Time"].get<>();

        std::vector<std::string> names = splitList(namesStr, ';');

        // Create availability stuct based on time data in file
        std::vector<std::string> tokens = splitList(availabilityStr, ';');
        Availability availability = {tokens[0], std::stoi(tokens[1]), std::stoi(tokens[2])};

        sessions.push_back(Session{id, names, course, availability});
    }

    return sessions;
}

void FileHandler::saveSessions(const std::vector<Session>& sessions) {
    std::ofstream sessionFile(AVAILABILITY_PATH);
    sessionFile << "SessionID,Students,Course,Time\n";

    for (Session session : sessions)
        sessionFile << session.toData();

    sessionFile.close();
}

std::vector<Student> FileHandler::loadProfiles() {
    std::vector<Student> students;
    csv::CSVReader reader(PROFILE_PATH, csv::CSVFormat().header_row(0));

    for (csv::CSVRow& row : reader) {
        // Get data from csv style rows
        std::string name = row["Name"].get<>();
        std::string id = row["StudentID"].get<>();
        std::string coursesStr = row["Courses"].get<>();
        std::string availabilityStr = row["Availability"].get<>();

        std::vector<std::string> courses = splitList(coursesStr, ';');

        std::vector<Availability> availability;
        std::vector<std::string> tokens = splitList(availabilityStr, ';');

        // Load in availability tokens (every three tokens contains info for one availability struct)
        for (size_t i = 0; i + 2 < tokens.size(); i += 3) {
            availability.push_back({
                tokens[i],
                std::stoi(tokens[i + 1]),
                std::stoi(tokens[i + 2])
            });
        }

        students.push_back(Student{id, name, courses, availability});
    }

    return students;
}

void FileHandler::saveProfiles(const std::vector<Student>& students) {
    std::ofstream profileFile(PROFILE_PATH);
    profileFile << "Name,StudentID,Courses,Availability\n";

    for (Student student : students)
        profileFile << student.toData();

    profileFile.close();
}
