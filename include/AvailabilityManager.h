#ifndef AVAILABILITY_MANAGER_H
#define AVAILABILITY_MANAGER_H

#include "Models/Student.h"

/**
 * @brief Manages addition, removal, and updating of availability times for students.
 */
class AvailabilityManager {
 public:
    /**
     * @brief Adds a new availability time slot to the student's profile.
     * @param student Reference to the Student whose availability is to be updated.
     */
    void addAvailability(Student& student);

    /**
     * @brief Removes an existing availability time slot from the student's profile.
     * @param student Reference to the Student whose availability is to be updated.
     */
    void removeAvailability(Student& student);

    /**
     * @brief Updates an existing availability time slot for the student.
     * @param student Reference to the Student whose availability is to be updated.
     */
    void updateAvailability(Student& student);
};

#endif // AVAILABILITY_MANAGER_H
