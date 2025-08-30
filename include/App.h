#ifndef APP_H
#define APP_H

#include <vector>
#include <string>

// Managers
#include "ProfileManager.h"
#include "AvailabilityManager.h"
#include "PartnerMatcher.h"
#include "SessionScheduler.h"
#include "FileHandler.h"

// Models
#include "Models/Student.h"
#include "Models/Session.h"

/**
 * @brief The App class serves as the main controller for the Study Buddy Scheduling App.
 * 
 * It handles user interaction, menu display, and delegates functionality
 * to the appropriate manager classes. It also handles data persistence
 * through FileHandler.
 */
class App {
 private:
    std::vector<Student> students;       ///< All loaded student profiles
    std::vector<Session> sessions;       ///< All scheduled study sessions
    Student* currentStudent = nullptr;   ///< Currently logged-in student

    // Manager Instances
    ProfileManager profileManager;
    AvailabilityManager availabilityManager;
    PartnerMatcher partnerMatcher;
    SessionScheduler sessionScheduler;
    FileHandler fileHandler;

    // File paths (can be constants or configurable later)
    const std::string profilesFile = "profiles.txt";
    const std::string sessionsFile = "sessions.txt";

 public:
    /**
     * @brief Initializes the app by loading data from files.
     */
    void initialize();

    /**
     * @brief Runs the main application loop (menu and input handling).
     */
    void run();

 private:
    /**
     * @brief Displays the main menu and processes user input.
     */
    void displayMenu();

    /**
     * @brief Handles profile creation and login.
     */
    void handleCreateOrLogin();

    /**
     * @brief Allows the current student to edit their profile.
     */
    void handleEditProfile();

    /**
     * @brief Allows the current student to manage availability.
     */
    void handleAvailability();

    /**
     * @brief Finds and displays possible study partners.
     */
    void handleSearchPartners();

    /**
     * @brief Displays suggested sessions with matching partners.
     */
    void handleSuggestedSessions();

    /**
     * @brief Confirms a study session between users.
     */
    void handleConfirmSession();

    /**
     * @brief Saves all data to local files.
     */
    void saveData();
};

#endif // APP_H
