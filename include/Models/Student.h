#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "Availability.h"

struct Student {
    std::string id;
    std::string name;
    std::vector<std::string> courses;
    std::vector<Availability> availability;

    std::string toString() const;
};

#endif // STUDENT_H
