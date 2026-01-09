#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  printf(1, "Initial virtual pages: %d\n", numvp());

  sbrk(4096);
  printf(1, "After 1 page sbrk: %d\n", numvp());

  sbrk(8192);
  printf(1, "After 2 more pages sbrk: %d\n", numvp());

  exit();
}
