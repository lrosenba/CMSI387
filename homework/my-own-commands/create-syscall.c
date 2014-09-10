#include <syscall.h> 
#include <linux/types.h>
#include <unistd.h>
#include <stdio.h> 
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
	syscall(8, 0, argv[0], 0744);
}