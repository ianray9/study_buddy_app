#include <algorithm>
#include <unordered_set>
#include <sstream>
#include <string>
#include "SessionScheduler.h"
#include "PartnerMatcher.h"

// Helper function to generate a session ID from names and course
std::string generateSessionID(const std::vector<std::string>& names, const std::string& course) {
    std::ostringstream idStr;

    for (std::string name : names) {
        if (name.length() > 2)
            idStr << name[0] << name[1];
        else
            idStr << "xx";
    }

    idStr << course;
    return idStr.str();
}

std::vector<Session> SessionScheduler::suggestSessions(const Student& student, const std::vector<Student>& allStudents) {
    PartnerMatcher matcher;
    std::vector<Student> matches = matcher.findMatchingStudents(student, allStudents);
    std::vector<Session> suggestions;

    for (Student match : matches) {
        // Find shared courses
        std::unordered_set<std::string> courseSet(student.courses.begin(), student.courses.end());
        std::vector<std::string> sharedCourses;
        for (std::string course : match.courses) {
            if (courseSet.count(course)) {
                sharedCourses.push_back(course);
            }
        }

        // Find overlapping availability
        for (Availability timeOne : student.availability) {
            for (Availability timeTwo : match.availability) {
                if (timeOne.day == timeTwo.day && timeOne.overlapsWith(timeTwo)) {
                    Availability overlap = {
                        timeOne.day,
                        std::max(timeOne.startHour, timeTwo.startHour),
                        std::min(timeOne.endHour, timeTwo.endHour)
                    };

                    for (const auto& course : sharedCourses) {
                        Session session;
                        session.studentNames = { student.name, match.name };
                        session.course = course;
                        session.timeSlot = overlap;
                        session.sessionID = generateSessionID(session.studentNames, course);
                        suggestions.push_back(session);
                    }
                }
            }
        }
    }

    return suggestions;
}

Session SessionScheduler::confirmSession(const Student& student1, const Student& student2, const std::string& course, const Availability& timeSlot) {
    Session session;
    session.studentNames = { student1.name, student2.name };
    session.course = course;
    session.timeSlot = timeSlot;
    session.sessionID = generateSessionID(session.studentNames, course);
    return session;
}
