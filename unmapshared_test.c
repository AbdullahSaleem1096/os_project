#include "types.h"
#include "user.h"

int
main(void)
{
  int *p = mapshared();

  p[0] = 42;
  printf(1, "value = %d\n", p[0]);

  unmapshared(p);

  printf(1, "unmap done\n");

  exit();
}
