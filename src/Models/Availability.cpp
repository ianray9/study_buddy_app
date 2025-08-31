#include "Models/Availability.h"
#include <sstream>

std::string Availability::toString() const {
    std::ostringstream time;
    bool pmStart = startHour >= 12;
    bool pmEnd = endHour >= 12;

    time << day << " ";
    time << (pmStart ? startHour - 12 : startHour) + (startHour == 12 ? + 12 : 0) << (pmStart ? "pm" : "am");
    time << "-";
    time << (pmEnd ? endHour - 12 : endHour) + (endHour == 12 ? + 12 : 0) << (pmEnd ? "pm" : "am");

    return time.str();
}

std::string Availability::toData() const {
    std::ostringstream timeData;
    timeData << day << ";" << startHour << ";" << endHour;

    return timeData.str();
}

bool Availability::overlapsWith(const Availability& other) const {
    if (day != other.day) {
        return false; 
    }
    return (startHour < other.endHour && endHour > other.startHour);
}