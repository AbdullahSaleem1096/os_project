#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  printf(1, "Initial VP: %d PP: %d\n", numvp(), numpp());

  sbrk(4096);
  printf(1, "After 1 page sbrk VP: %d PP: %d\n", numvp(), numpp());

  exit();
}
