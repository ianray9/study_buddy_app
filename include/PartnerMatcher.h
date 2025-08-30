#ifndef PARTNER_MATCHER_H
#define PARTNER_MATCHER_H

#include <vector>
#include "Models/Student.h"

/**
 * @brief Responsible for finding matching study partners based on courses and availability.
 */
class PartnerMatcher {
 public:
    /**
     * @brief Finds students who share courses and have overlapping availability.
     * @param student The student seeking study partners.
     * @param allStudents The list of all students to search within.
     * @return A vector of matching Student objects.
     */
    std::vector<Student> findMatchingStudents(
      const Student& student, const std::vector<Student>& allStudents);
};

#endif // PARTNER_MATCHER_H
