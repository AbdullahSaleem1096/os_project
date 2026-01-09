#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

#include "spinlock.h"

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int count = 0;

struct spinlock pc_lock;

// wait channels
void *not_full = (void*)1;
void *not_empty = (void*)2;

int
sys_getptsize(void)
{
  return count_pt_pages(myproc());
}

int
sys_numvp(void)
{
  struct proc *p = myproc();
  return (p->sz + PGSIZE - 1) / PGSIZE;
}

int
sys_numpp(void)
{
  return count_physical_pages(myproc());
}


int
sys_produce(void)
{
    int item;

    if (argint(0, &item) < 0)
        return -1;

    acquire(&pc_lock);

    while (count == BUFFER_SIZE) {
        sleep(not_full, &pc_lock);
    }

    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    count++;

    wakeup(not_empty);
    release(&pc_lock);

    return 0;
}

int
sys_consume(void)
{
    int item;

    acquire(&pc_lock);

    while (count == 0) {
        sleep(not_empty, &pc_lock);
    }

    item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    count--;

    wakeup(not_full);
    release(&pc_lock);

    return item;
}


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_set_priority(void)
{
  int priority;
  // Fetch the integer argument from the stack
  if(argint(0, &priority) < 0)
    return -1;
  return set_priority(priority);
}