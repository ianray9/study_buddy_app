#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <vector>
#include <string>
#include "Models/Student.h"
#include "Models/Session.h"

/**
 * @brief Handles loading and saving of student profiles and study sessions from/to files.
 */
class FileHandler {
 public:
    /**
     * @brief Loads student profiles from a specified file.
     * @param filename The path to the profiles file.
     * @return A vector containing all loaded Student objects.
     */
    std::vector<Student> loadProfiles(const std::string& filename);

    /**
     * @brief Saves all student profiles to a specified file.
     * @param students The vector of Student objects to save.
     * @param filename The path to the profiles file.
     */
    void saveProfiles(const std::vector<Student>& students, const std::string& filename);

    /**
     * @brief Loads scheduled study sessions from a specified file.
     * @param filename The path to the sessions file.
     * @return A vector containing all loaded Session objects.
     */
    std::vector<Session> loadSessions(const std::string& filename);

    /**
     * @brief Saves all scheduled study sessions to a specified file.
     * @param sessions The vector of Session objects to save.
     * @param filename The path to the sessions file.
     */
    void saveSessions(const std::vector<Session>& sessions, const std::string& filename);
};

#endif // FILE_HANDLER_H
