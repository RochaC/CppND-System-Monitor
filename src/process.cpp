#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// Return this process's ID
int Process::Pid() { return pid_; }

// Return this process's CPU utilization
float Process::CpuUtilization() const {
    string line;
    string value;
    float result;
    std::ifstream filestream(LinuxParser::kProcDirectory + std::to_string(pid_) + LinuxParser::kStatFilename);
    getline(filestream, line);
    string str = line;
    std::istringstream buf(str);
    std::istream_iterator<string> beg(buf), end;
    vector<string> values(beg, end); // done!

    // acquiring relevant times for calculation of active occupation of CPU for selected process
    float utime = LinuxParser::UpTime(pid_);
    float stime = stof(values[14]);
    float cutime = stof(values[15]);
    float cstime = stof(values[16]);
    float starttime = stof(values[21]);
    float uptime = LinuxParser::UpTime();
    float freq = sysconf(_SC_CLK_TCK);
    float total_time = utime + stime + cutime + cstime;
    float seconds = uptime - (starttime / freq);
    result = (float) 100.0 * ((total_time / freq) / seconds);

    return result;
}

// Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const &a) const {
    const float cpu1 = CpuUtilization();
    float cpu2 = a.CpuUtilization();

    return cpu1 < cpu2;
}