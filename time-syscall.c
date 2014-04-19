#include <linux/types.h>
#include <linux/unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>

int main(int argc, char* argv[]) {
    int secs = syscall(13);
    double mins = floor(secs/60);
    double hours = floor(mins/60);
    int minutes = (int)mins % 60;
    char *c = ":";
    syscall(4, 0, hours);
    syscall(4, 0, c, strlen(c));
    syscall(4, 0, minutes);
}

