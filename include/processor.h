#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>


typedef struct {
  long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
} cpudata_t;


class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  void getProcDataAll();
  std::string getMemoryUtilization();

  // TODO: Declare any necessary private members
 private:
  std::string user;
  cpudata_t actualCPUdata;
  cpudata_t prevCPUdata;
};



#endif