#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
  int old_prio; // Removed unused 'new_prio'

  printf(1, "\n--- EDGE CASE TEST ---\n");

  // Check 1: Verify Default Priority is 10
  // We set to 15, and expect the return value to be the previous (10)
  printf(1, "1. Checking return value mechanism...\n");
  old_prio = set_priority(15);
  
  if(old_prio == 10) {
      printf(1, "   [PASS] Old priority was 10, now set to 15.\n");
  } else {
      printf(1, "   [FAIL] Expected old priority 10, got %d.\n", old_prio);
  }

  // Check 2: Negative Priority
  printf(1, "2. Setting Negative Priority (-5)...\n");
  set_priority(-5); 
  printf(1, "   [PASS] System did not crash with negative input.\n");

  // Check 3: Priority Lowering Yield
  printf(1, "3. Rapid priority switching...\n");
  set_priority(100);
  set_priority(1);
  printf(1, "   [PASS] Switched 100 -> 1 without crash.\n");

  printf(1, "--- EDGE TEST COMPLETE ---\n");
  exit();
}