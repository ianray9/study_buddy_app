#ifndef SESSION_SCHEDULER_H
#define SESSION_SCHEDULER_H

#include <vector>
#include <string>
#include "Models/Student.h"
#include "Models/Session.h"
#include "Models/Availability.h"

/**
 * @brief Manages scheduling, suggesting, and confirming study sessions between students.
 */
class SessionScheduler {
 public:
    /**
     * @brief Suggests possible study sessions based on matched students and shared availability.
     * @param student The student requesting session suggestions.
     * @param matches The list of matched students.
     * @return A vector of suggested Session objects.
     */
    std::vector<Session> suggestSessions(const Student& student, const std::vector<Student>& matches);

    /**
     * @brief Confirms a study session between two students at a specific time and course.
     * @param student1 The first student.
     * @param student2 The second student.
     * @param course The course for the study session.
     * @param timeSlot The agreed upon availability time slot.
     * @return A newly created Session object representing the confirmed session.
     */
    Session confirmSession(const Student& student1, const Student& student2, const std::string& course, const Availability& timeSlot);
};

#endif // SESSION_SCHEDULER_H
