#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <vector>
#include "Availability.h"

struct Session {
    std::string sessionId;
    std::vector<std::string> studentNames;
    std::string course;
    Availability timeSlot;

    std::string toString() const;
};

#endif // SESSION_H
