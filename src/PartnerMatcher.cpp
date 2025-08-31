#include "PartnerMatcher.h"
#include <algorithm>

std::vector<Student> PartnerMatcher::findMatchingStudents(
    const Student& student,
    const std::vector<Student>& allStudents)
{
    std::vector<Student> matches;

    for (const auto& otherStudent : allStudents) {
        // Skip comparing with self
        if (otherStudent.id == student.id) {
            continue;
        }

        //  Check if they share at least one course
        bool sharesCourse = false;
        for (const auto& course : student.courses) {
            if (std::find(otherStudent.courses.begin(),
                          otherStudent.courses.end(),
                          course) != otherStudent.courses.end()) {
                sharesCourse = true;
                break;
            }
        }
        if (!sharesCourse) {
            continue;
        }

        // Check if availability overlaps 
        bool overlaps = false;
        for (const auto& a1 : student.availability) {
            for (const auto& a2 : otherStudent.availability) {
                if (a1.day == a2.day && a1.overlapsWith(a2)) {
                    overlaps = true;
                    break;
                }
            }
            if (overlaps) break;
        }

        // Add to matches if both conditions satisfied 
        if (overlaps) {
            matches.push_back(otherStudent);
        }
    }

    return matches;
}