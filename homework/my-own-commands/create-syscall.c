//#include <syscall.h> 
#include <linux/types.h>
#include <linux/unistd.h>
#include <stdio.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
        if (argc != 3) {
           printf("usage: %s <filename> <octal mode>\n", argv[0]);
           printf("  where filename is the name of the file to create\n");
           printf("  and   octal mode is the file permission mask\n");
           exit(EXIT_FAILURE);
        } 
        int ret = syscall(8, argv[1], (int)strtol(argv[2], NULL, 8));
        if (ret == -1) {
           perror("syscall 8");
        }
}
