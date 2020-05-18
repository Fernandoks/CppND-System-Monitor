#include "ncurses_display.h"
#include "system.h"

#include "linux_parser.h"
#include "processor.h"

//#define DEBUG
#ifndef DEBUG
#define TEST  
#endif

int main() {
  System system;

#ifdef TEST
  NCursesDisplay::Display(system);
#endif

#ifdef DEBUG
  float memory = LinuxParser::MemoryUtilization(); //ok
  int processes = LinuxParser::TotalProcesses(); //ok
  int runningProcesses =  LinuxParser::RunningProcesses() ;//ok
  long uptime =  LinuxParser::UpTime(); // ok
  LinuxParser::ProcData("cpu"); //ok

  Processor Proc;
  float a = Proc.Utilization();
   a = Proc.Utilization();
   a = Proc.Utilization();
#endif
}