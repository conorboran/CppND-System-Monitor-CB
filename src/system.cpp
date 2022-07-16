#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
/*You need to complete the mentioned TODOs in order to satisfy the rubric criteria "The student will be able to extract and display basic data about the system."

You need to properly format the uptime. Refer to the comments mentioned in format. cpp for formatting the uptime.*/

// DONE: Return the system's CPU
Processor& System::Cpu()
{
    return cpu_;
}

// DONE: Return a container composed of the system's processes
vector<Process>& System::Processes()
{
    vector<int> pids = LinuxParser::Pids();
    long int up_time_in = 0;
    long system_uptime = LinuxParser::UpTime();

    processes_.clear();
    while(!pids.empty())
    {
        Process process;
        process.SetPid(pids.back());
        process.SetCommand(LinuxParser::Command(pids.back()));
        process.SetRam(LinuxParser::Ram(pids.back()));
        process.SetUser(LinuxParser::User(pids.back()));
        process.SetUpTime(LinuxParser::UpTime(pids.back()));
        long total_time = LinuxParser::ActiveJiffies(pids.back()) / sysconf(_SC_CLK_TCK);
        long seconds = system_uptime - up_time_in;
        process.SetCpuUtilization(float(total_time) / float(seconds));

        processes_.push_back(process);
        pids.pop_back();
    }
    std::sort(processes_.begin(), processes_.end());
    return processes_;
}

// DONE: Return the system's kernel identifier (string)
std::string System::Kernel()
{
    std::string kernel = LinuxParser::Kernel();
    return kernel;
}

// DONE: Return the system's memory utilization
float System::MemoryUtilization()
{
    float mem_utilization = LinuxParser::MemoryUtilization();
    return mem_utilization;
}

// DONE: Return the operating system name
std::string System::OperatingSystem()
{
    std::string operating_system = LinuxParser::OperatingSystem();
    return operating_system;
}

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses()
{
    int running_processes = LinuxParser::RunningProcesses();
    return running_processes;
}

// DONE: Return the total number of processes on the system
int System::TotalProcesses()
{
    int total_processes = LinuxParser::TotalProcesses();
    return total_processes;
}

// DONE: Return the number of seconds since the system started running
long int System::UpTime()
{
    long up_time = LinuxParser::UpTime();
    return up_time;
}
