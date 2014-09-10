#include <linux/types.h>
#include <linux/unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
     if (argc != 3) {
           printf("usage: %s <current filename> <new filename>\n", argv[0]);
           printf("  where current filename is the current name of the file\n");
           printf("  and new filename is the name that will replace the current filename\n");
           exit(EXIT_FAILURE);
     }

     int ret = syscall(38, argv[1], argv[2]);
     if (ret == -1) {
           perror("syscall 38");
     }
}
