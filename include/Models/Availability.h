#ifndef AVAILABILITY_H
#define AVAILABILITY_H

#include <string>

struct Availability {
    std::string day;      // e.g., "Monday"
    int startHour;        // 24-hour format, e.g., 14 for 2 PM
    int endHour;          // e.g., 16 for 4 PM

    std::string toString() const;
    std::string toData() const;

    bool overlapsWith(const Availability& other) const;
};

#endif // AVAILABILITY_H
