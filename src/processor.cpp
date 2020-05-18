#include "processor.h"

#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {

  std::vector<long> cpuData = LinuxParser::ProcData("cpu");
  actualCPUdata.user = cpuData[0];
  actualCPUdata.nice = cpuData[1];
  actualCPUdata.system = cpuData[2];
  actualCPUdata.idle = cpuData[3];
  actualCPUdata.iowait = cpuData[4];
  actualCPUdata.irq = cpuData[5];
  actualCPUdata.softirq = cpuData[6];
  actualCPUdata.steal = cpuData[7];
  actualCPUdata.guest = cpuData[8];
  actualCPUdata.guest_nice = cpuData[9];
  cpuData.empty();

  long PrevIdle = prevCPUdata.idle + prevCPUdata.iowait;
  long Idle = actualCPUdata.idle + actualCPUdata.iowait;

  long PrevNonIdle = prevCPUdata.user + prevCPUdata.nice + prevCPUdata.system +
                     prevCPUdata.irq + prevCPUdata.softirq + prevCPUdata.steal;
  long NonIdle = actualCPUdata.user + actualCPUdata.nice +
                 actualCPUdata.system + actualCPUdata.irq +
                 actualCPUdata.softirq + actualCPUdata.steal;

  long PrevTotal = PrevIdle + PrevNonIdle;
  long Total = Idle + NonIdle;

  // differentiate: actual value minus the previous one
  long totald = Total - PrevTotal;
  long idled = Idle - PrevIdle;

  float CPU_Percentage = (float(totald - idled) / float(totald));

  prevCPUdata = actualCPUdata;

  return CPU_Percentage;
}

std::string Processor::getMemoryUtilization()
{ 
  return (std::to_string(LinuxParser::MemoryUtilization()));
}


void Processor::getProcDataAll() {
  const std::string kCpuName{"cpu"};
  std::map<std::string, std::vector<long>> cpus;
  std::string nCpu;
  int i = 0;

  // Get cpu data
  cpus.emplace(kCpuName, LinuxParser::ProcData(kCpuName));

  // Get other cpu info
  do {
    nCpu = kCpuName + std::to_string(i++);
    cpus.emplace(nCpu, LinuxParser::ProcData(nCpu));
  } while (cpus[nCpu].back() != -1);
}

