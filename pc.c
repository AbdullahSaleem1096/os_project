#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
    int pid = fork();

    if (pid == 0) {
        // Consumer
        while (1) {
            int item = consume();   // your syscall
            printf(1, "Consumed: %d\n", item);
            sleep(10);
        }
    } else {
        // Producer
        int i = 0;
        while (1) {
            printf(1, "Produced: %d\n", i);
            produce(i++);           // your syscall
            sleep(10);
        }
    }
    exit();
}
