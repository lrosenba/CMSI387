#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

#define _NR_hello_world 349

long hello_world_syscall(void) {
    return syscall(_NR_hello_world);
}

int main(int argc, char *argv[]) {
    long int a = hello_world_syscall();
    printf("System call returned %Id\n", a);
    return 0;
}
