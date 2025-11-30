#include "types.h"
#include "stat.h"
#include "user.h"

void waste_time() {
  int i;
  for (i = 0; i < 50000000; i++) {
    asm("nop");
  }
}

int main(int argc, char *argv[]) {
  int i, pid;
  int total_procs = 20;

  printf(1, "\n--- STRESS TEST (20 Processes) ---\n");

  for (i = 0; i < total_procs; i++) {
    pid = fork();
    if (pid == 0) {
      // Even indices = Low Priority, Odd indices = High Priority
      if (i % 2 == 0) {
        set_priority(5); 
        // Silent work for cleaner output, only print finish
        waste_time();
        printf(1, "LOW  Priority (5)  Process %d finished\n", getpid());
      } else {
        set_priority(50);
        waste_time();
        printf(1, "HIGH Priority (50) Process %d finished\n", getpid());
      }
      exit();
    }
  }

  // Parent waits for all children
  for (i = 0; i < total_procs; i++) {
    wait();
  }

  printf(1, "--- STRESS TEST COMPLETE ---\n");
  exit();
}