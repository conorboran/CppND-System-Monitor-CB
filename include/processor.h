#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"

class Processor {
 public:
  Processor()
  {
    prev_idle_ = 0;
    prev_non_idle_ = 0;
    prev_total_ = 0;
  }
  float Utilization();  // DONE: See src/processor.cpp

  // DONE: Declare any necessary private members
 private:
  long prev_idle_;
  long prev_non_idle_;
  long prev_total_;
};

#endif