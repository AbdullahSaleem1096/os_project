#include "types.h"
#include "user.h"

int
main(void)
{
  int *p = mapshared();

  if(p == 0){
    printf(1, "mapshared failed\n");
    exit();
  }

  if(fork() == 0){
    *p = 42;
    printf(1, "child %d\n", *p);
    exit();
  }

  wait();
  printf(1, "parent %d\n", *p);

  exit();
}
