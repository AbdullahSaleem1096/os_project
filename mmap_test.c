#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"

int
main(void)
{
  int *p;

  printf(1, "Before mmap:\n");
  printf(1, "VP=%d PP=%d\n\n", numvp(), numpp());

  // Request 3 pages of virtual memory
  p = (int*)mmap(3 * PGSIZE);

  if(p == (int*)-1){
    printf(1, "mmap failed\n");
    exit();
  }

  printf(1, "After mmap (no access yet):\n");
  printf(1, "VP=%d PP=%d\n\n", numvp(), numpp());

  // Touch first page
  p[0] = 1;
  printf(1, "After touching first page:\n");
  printf(1, "VP=%d PP=%d\n\n", numvp(), numpp());

  // Touch second page (1024 ints = 4096 bytes)
  p[1024] = 2;
  printf(1, "After touching second page:\n");
  printf(1, "VP=%d PP=%d\n\n", numvp(), numpp());

  // Touch third page
  p[2048] = 3;
  printf(1, "After touching third page:\n");
  printf(1, "VP=%d PP=%d\n\n", numvp(), numpp());

  exit();
}
