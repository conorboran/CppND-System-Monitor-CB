#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // DONE: See src/process.cpp
  std::string User();                      // DONE: See src/process.cpp
  std::string Command();                   // DONE: See src/process.cpp
  float CpuUtilization();                  // DONE: See src/process.cpp
  std::string Ram();                       // DONE: See src/process.cpp
  long int UpTime();                       // DONE: See src/process.cpp
  bool operator<(Process const& a) const;  // DONE: See src/process.cpp
  void SetPid(int pid_in);
  void SetUser(std::string username_in);
  void SetCommand(std::string command_in);
  void SetCpuUtilization(float cpu_utilization_in);
  void SetRam(std::string ram_in);
  void SetUpTime(long int up_time_in);

  // DONE: Declare any necessary private members
 private:
  int pid_;
  std::string username_;
  std::string command_;
  float cpu_utilization_;
  std::string ram_;
  long int up_time_;
};

#endif