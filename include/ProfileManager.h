#ifndef PROFILE_MANAGER_H
#define PROFILE_MANAGER_H

#include "Models/Availability.h"
#define ID_PATH "data/currentID.txt"

#include <vector>
#include <string>
#include "Models/Student.h"

/**
 * @brief Manages creation and editing of student profiles.
 */
class ProfileManager {
 public:
   /**
     * @brief Helper function to prompt user for enrolled courses.
     * @return List of enrolled courses
     */
    std::vector<std::string> getCourses();

   /**
     * @brief Helper function to prompt user for time availability
     * @return List of times the user is available
     */
    std::vector<Availability> getTimes();

    /**
     * @brief Creates a new student profile by gathering user input.
     * @return A newly created Student object.
     */
    Student createProfile();

    /**
     * @brief Allows editing of an existing student profile.
     * @param student Reference to the Student to be edited.
     */
    void editProfile(Student& student);
};

#endif // PROFILE_MANAGER_H
