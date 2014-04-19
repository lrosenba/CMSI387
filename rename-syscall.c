#include <linux/types.h>
#include <linux/unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    syscall(38, argv[1], argv[2]);
}
