#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid()
{
    return pid_;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization()
{
    return cpu_utilization_;
}

// TODO: Return the command that generated this process
string Process::Command()
{
    return command_;
}

// TODO: Return this process's memory utilization
string Process::Ram()
{
    return ram_;
}

// TODO: Return the user (name) that generated this process
string Process::User()
{
    return username_;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime()
{
    return up_time_;
}

// TODO: Overload the "less than" comparison operator for Process objects (sorting by cpu utilization)
bool Process::operator<(Process const& a) const
{
    return std::stoi(this->ram_) > std::stoi(a.ram_);
}

void Process::SetPid(int pid_in)
{
    pid_ = pid_in;
}

void Process::SetUser(std::string username_in)
{
    username_ = username_in;
}

void Process::SetCommand(std::string command_in)
{
    command_ = command_in;
}

void Process::SetCpuUtilization(float cpu_utilization_in)
{
    cpu_utilization_ = cpu_utilization_in;
}

void Process::SetRam(std::string ram_in)
{
    ram_ = ram_in;
}

void Process::SetUpTime(long int up_time_in)
{
    up_time_ = up_time_in;
}
