#include "types.h"
#include "stat.h"
#include "user.h"

void waste_time() {
  int i;
  for (i = 0; i < 200000000; i++) {
    asm("nop");
  }
}

int main(int argc, char *argv[]) {
  int pid1, pid2;

  printf(1, "\n--- BASIC FUNCTIONALITY TEST ---\n");

  // Create Low Priority Process
  pid1 = fork();
  if (pid1 == 0) {
    set_priority(5); // Low Priority
    printf(1, " [Start] Process A (Low Prio 5) started.\n");
    waste_time();
    printf(1, " [End]   Process A (Low Prio 5) finished.\n");
    exit();
  }

  // Create High Priority Process
  pid2 = fork();
  if (pid2 == 0) {
    set_priority(20); // High Priority
    printf(1, " [Start] Process B (High Prio 20) started.\n");
    waste_time();
    printf(1, " [End]   Process B (High Prio 20) finished.\n");
    exit();
  }

  wait();
  wait();
  printf(1, "--- TEST COMPLETE ---\n");
  exit();
}