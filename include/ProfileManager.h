#ifndef PROFILE_MANAGER_H
#define PROFILE_MANAGER_H

#include <vector>
#include "Models/Student.h"

/**
 * @brief Manages creation and editing of student profiles.
 */
class ProfileManager {
 public:
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
