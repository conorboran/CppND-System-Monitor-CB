#include "processor.h"

// DONE: Return the aggregate CPU utilization
float Processor::Utilization()
{
    std::vector<std::string> cpu = LinuxParser::CpuUtilization();
    long user_time = stol(cpu.at(0));
    long nice_time = stol(cpu.at(1));
    long system = stol(cpu.at(2));
    long idle_time = stol(cpu.at(3));
    long iowait = stol(cpu.at(4));
    long irq = stol(cpu.at(5));
    long soft_irq = stol(cpu.at(6));
    long steal = stol(cpu.at(7));
    long guest = stol(cpu.at(8));
    long guest_nice = stol(cpu.at(9));

    user_time -= guest;
    nice_time -= guest_nice;

    long idle_all_time = idle_time + iowait;
    long system_all_time = system + irq + soft_irq;
    long virtual_time = guest + guest_nice;
    long non_idle = user_time + nice_time + system_all_time + steal;
    long total_time = non_idle + idle_all_time + virtual_time;
    prev_total_ = prev_idle_ + prev_non_idle_;

    long total_diff = total_time - prev_total_;
    long idle_diff = idle_all_time - prev_idle_;

    prev_idle_ = idle_all_time;
    prev_non_idle_ = non_idle;
    return (float(total_diff) - float(idle_diff)) / float(total_diff);
}
