#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  printf(1, "Page table size: %d pages\n", getptsize());

  sbrk(4096);
  printf(1, "After sbrk, page table size: %d pages\n", getptsize());

  exit();
}
