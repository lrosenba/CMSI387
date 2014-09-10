#include <linux/types.h>
#include <linux/unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

//This program will print the current time

int main(int argc, char* argv[]) {
    long secs;
    struct tm *time;
    char buff[80];
    int ret = syscall(13, &secs);
    time = localtime(&secs);
    strftime(buff, 80, "%x - %I:%M%p %Z", time);
    printf("%s\n", buff);
    if (ret == -1) {
           perror("syscall 13");
    }
}

