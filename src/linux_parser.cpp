#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization()
{
  float mem_total = 0.0; //in KB
  float mem_free = 0.0;  //in KB
  float total_used_memory = 0.0; //in KB
  string line, info_name;
  float info_value;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);

  while(stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> info_name >> info_value;

    if(info_name == "MemTotal:")
    {
      mem_total = info_value;
    }
    if(info_name == "MemFree:")
    {
      mem_free = info_value;
    }
    if(mem_total > 0.0 && mem_free > 0.0)
    {
      break;
    }
  }

  total_used_memory = mem_total - mem_free;

  return total_used_memory / mem_total; //return fraction of used memory to total
}

// DONE: Read and return the system uptime
long LinuxParser::UpTime()
{
  long up_time = 0.0; //in seconds
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);

  if(stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> up_time;
  }

  return up_time;
}

// DONE: Read and return the number of jiffies for the system
long LinuxParser::Jiffies()
{
  long total_jiffies = 0;
  int system_index = 10;
  string line, stream_in;
  std::ifstream stream(kProcDirectory + kStatFilename);

  if(stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for(int i = 0; i <= system_index; i++)
    {
      linestream >> stream_in;
      if(i != 0)
      {
        total_jiffies += std::stol(stream_in);
      }
    }
  }
  return total_jiffies;
}

// DONE: Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid)
{
  long active_jiffies = 0;
  int system_index = 17;
  string line, stream_in;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);

  if(stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for(int i = 1; i <= system_index; i++)
    {
      linestream >> stream_in;
      if(i >= 14 && i <=17)
      {
        active_jiffies += std::stol(stream_in);
      }
    }
  }

  return active_jiffies;
}

// DONE: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies()
{
  long active_jiffies = 0;
  int system_index = 10;
  string line, stream_in;
  std::ifstream stream(kProcDirectory + kStatFilename);

  if(stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for(int i = 0; i <= system_index; i++)
    {
      linestream >> stream_in;
      if(i != 0 && i != 4 && i != 5)
      {
        active_jiffies += std::stol(stream_in);
      }
    }
  }
  return active_jiffies;
}

// DONE: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies()
{
  long idle_jiffies = 0;
  int system_index = 10;
  string line, stream_in;
  std::ifstream stream(kProcDirectory + kStatFilename);

  if(stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for(int i = 0; i <= system_index; i++)
    {
      linestream >> stream_in;
      if(i == 4 || i == 5)
      {
        idle_jiffies += std::stol(stream_in);
      }
    }
  }
  return idle_jiffies;
}

// DONE: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization()
{
  string line, stream_in;
  int system_index = 10;
  vector<string> cpu_fields;

  std::ifstream stream(kProcDirectory + kStatFilename);

  if(stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for(int i = 0; i <= system_index; i++)
    {
      linestream >> stream_in;
      if(i != 0)
      {
        cpu_fields.push_back(stream_in);
      }
    }
  }
  return cpu_fields;
}

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses()
{
  string line, info_name;
  int total_processes = 0;

  std::ifstream stream(kProcDirectory + kStatFilename);

  while(stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> info_name >> total_processes;

    if(info_name == "processes")
    {
      break;
    }
  }

  return total_processes;
}

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses()
{
  string line, info_name;
  int running_processes = 0;

  std::ifstream stream(kProcDirectory + kStatFilename);

  while(stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> info_name >> running_processes;

    if(info_name == "procs_running")
    {
      break;
    }
  }

  return running_processes;
}

// DONE: Read and return the command associated with a process
string LinuxParser::Command(int pid)
{
  string line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);

  if(stream.is_open())
  {
    std::getline(stream, line);
  }

  return line;
}

// DONE: Read and return the memory used by a process
string LinuxParser::Ram(int pid)
{
  int memory_utilized = 0U;
  int info_data = 0U;
  string line, info_name, ram;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);

  if(stream.is_open())
  {
    while(std::getline(stream, line))
    {
      std::istringstream linestream(line);
      linestream >> info_name >> info_data;
      if(info_name == "VmSize:")
      {
        memory_utilized = info_data;
        break;
      }
    }
  }

  ram = std::to_string(memory_utilized / 1000);
  return ram;
}

// DONE: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid)
{
  string line, info_data, info_name;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);

  if(stream.is_open())
  {
    while(std::getline(stream, line))
    {
      std::istringstream linestream(line);
      linestream >> info_name >> info_data;
      if(info_name == "Uid:")
      {
        break;
      }
    }
  }

  return info_data;
}

// DONE: Read and return the user associated with a process
string LinuxParser::User(int pid)
{
  string uid = LinuxParser::Uid(pid);
  string line, username, x, uid_in;

  std::ifstream stream(kPasswordPath);

  if(stream.is_open())
  {
    while(std::getline(stream, line))
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> username >> x >> uid_in;
      if(uid_in == uid)
      {
        break;
      }
    }
  }

  return username;
}

// DONE: Read and return the uptime of a process
long LinuxParser::UpTime(int pid)
{
  long start_time = 0.0; //in seconds
  int starttime_index = 22;
  string line, stream_in;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);

  if(stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for(int i = 1; i <= starttime_index; i++)
    {
      linestream >> stream_in;
    }
    start_time = std::stol(stream_in) / sysconf(_SC_CLK_TCK); // converted from clock ticks to seconds
  }

  long system_up_time = LinuxParser::UpTime();
  long process_up_time = system_up_time - start_time;
  return process_up_time; // divide clock ticks to get seconds
}
