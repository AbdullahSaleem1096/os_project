#include "types.h"
#include "stat.h"
#include "user.h"

// CPU waster function
void verify_priority(int k) {
  int i;
  for(i = 0; i < k; i++) {
     asm("nop"); 
  }
}

int main(int argc, char *argv[])
{
  int pid_low, pid_high;

  printf(1, "Testing Priority Scheduler...\n");

  pid_low = fork();
  if(pid_low == 0) {
    set_priority(5); // Low Priority
    printf(1, "Low Priority Process (5) starting work...\n");
    verify_priority(100000000); // Simulate work
    printf(1, "Low Priority Process Finished.\n");
    exit();
  }

  pid_high = fork();
  if(pid_high == 0) {
    set_priority(20); // High Priority
    printf(1, "High Priority Process (20) starting work...\n");
    verify_priority(100000000); // Simulate work
    printf(1, "High Priority Process Finished.\n");
    exit();
  }

  wait();
  wait();
  printf(1, "Test finished.\n");
  exit();
}