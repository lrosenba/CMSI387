#include <linux/types.h>
#include <linux/unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>

//This program will rename the file passed as the 1st argument to the 2nd argument

int main(int argc, char* argv[]) {
     char oldfile[512];
     char newfile[512];

     if (argc != 3) {
           printf("usage: %s <current filename> <new filename>\n", argv[0]);
           printf("  where current filename is the current name of the file\n");
           printf("  and new filename is the name that will replace the current filename\n");
           exit(EXIT_FAILURE);
     }
     
     //Verifying existence of the current file
     printf("Checking for existance of old file before rename syscall\n");
     sprintf(oldfile, "stat %s", argv[1]);
     system(oldfile);

     int ret = syscall(38, argv[1], argv[2]);
     if (ret == -1) {
           perror("syscall 38");
     }
     //Verify file was renamed
     printf("Checking for old file after rename syscall\n");
     sprintf(oldfile, "stat %s", argv[1]);
     system(oldfile);
     printf("Checking for new file\n");
     sprintf(newfile, "stat %s", argv[2]);
     system(newfile);
}





