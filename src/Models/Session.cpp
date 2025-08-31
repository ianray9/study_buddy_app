#include <sstream>
#include "Models/Session.h"

// ANSI Color Codes
#define RESET     "\033[0m"
#define BOLD_BLUE "\033[1;34m"
#define MAGENTA   "\033[35m"
#define CYAN      "\033[36m"

std::string Session::toString() const {
    std::ostringstream sessionOut;

    // Header
    std::ostringstream header;
    std::string headerStr = "Study Session: " + sessionID;
    header << BOLD_BLUE << headerStr << RESET;
    sessionOut << header.str() << "\n";

    // Separator line
    std::ostringstream plainHeader;
    plainHeader << "Study Session: " << sessionID;
    sessionOut << std::string(headerStr.length() + 2, '-') << "+>" << "\n";

    // Course
    sessionOut << MAGENTA << "Course:       " << RESET << course << "\n";

    // Time
    sessionOut << MAGENTA << "Time:         " << RESET << timeSlot.toString() << "\n";

    // Participants
    sessionOut << MAGENTA << "Participants: " << RESET;
    for (size_t i = 0; i < studentNames.size(); ++i) {
        sessionOut << studentNames[i];
        if (i != studentNames.size() - 1)
            sessionOut << ", ";
    }
    sessionOut << "\n";

    return sessionOut.str();
}

