#include <string>

#include "format.h"

using std::string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
    long minutes = seconds / 60;
    long hour = minutes / 60;
    long second = int(seconds % 60);
    long minute = int(minutes % 60);

    string str = string(std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second));

    return str;
}