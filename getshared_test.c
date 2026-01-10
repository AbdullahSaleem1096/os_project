#include "types.h"
#include "user.h"

int
main(void)
{
  printf(1, "Initially shared pages: %d\n", getshared());

  int *p = mapshared();
  printf(1, "After mapshared: %d\n", getshared());

  if(fork() == 0){
    printf(1, "Child sees shared: %d\n", getshared());
    exit();
  }

  wait();
  printf(1, "Parent sees shared: %d\n", getshared());

  exit();
}
