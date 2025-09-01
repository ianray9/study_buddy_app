#include <string>
#include <sstream>
#include "utils/Color.h"
#include "Models/Student.h"

std::string Student::toString() const {
    std::ostringstream student;

    // Header
    std::ostringstream header;
    header << BOLD_CYAN << "Student " << id << " | " << name << RESET;
    student << header.str() << "\n";

    // Separator line
    size_t lineLength = ("Student " + id + " | " + name).length();
    student << std::string(lineLength + 2, '-') << "+>" << "\n";

    // Labels
    const std::string availabilityLabel = "Availability:";
    const std::string enrollmentLabel = "Current Enrollment:";
    size_t alignCol = std::max(availabilityLabel.length(), enrollmentLabel.length()) + 1;

    // Current Enrollment
    student << YELLOW << enrollmentLabel << RESET;
    student << std::string(alignCol - enrollmentLabel.length(), ' ');
    for (size_t i = 0; i < courses.size(); i++) {
        student << courses[i];
        if (i != courses.size() - 1)
            student << ", ";
    }
    student << "\n";

    // Availability
    student << GREEN << availabilityLabel << RESET;
    student << std::string(alignCol - availabilityLabel.length(), ' ');
    for (size_t i = 0; i < availability.size(); i++) {
        student << availability[i].toString();
        if (i != availability.size() - 1)
            student << ", ";
    }

    student << "\n";
    return student.str();
}


std::string Student::toData() const {
    std::ostringstream profileData;

    profileData << name << ",";
    profileData << id << ",";

    // Write out Courses
    profileData << "\"";
    for (size_t i = 0; i < courses.size(); i++) {
        profileData << courses[i];
        if (i != courses.size() - 1) {
            profileData << ";";
        }
    }
    profileData << "\",";

    // Write out Availability
    profileData << "\"";
    for (size_t i = 0; i < availability.size(); i++) {
        profileData << availability[i].toData();
        if (i != availability.size() - 1) {
            profileData << ";";
        }
    }
    profileData << "\"";

    profileData << "\n";

    return profileData.str();
}
