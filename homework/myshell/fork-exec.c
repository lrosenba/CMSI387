#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/**
* This program demonstrates the use of the fork() and exec()
* functions.
*/

#define MAXTOKENS    256
#define MAXTOKENSIZE 256
#define MAXBUF       1024

int main() {
    char command[MAXBUF];
    char tmp_input[MAXBUF];
    char *whitespace = "\t \n"; 
    char *tokenArr[MAXTOKENS];
    char *tmp_memptr;
    int i;
    int ret_args;
    pid_t pid;
    
    for (i=0; i < MAXTOKENS; i+=1) {
         tokenArr[i] = malloc(MAXTOKENSIZE * sizeof(char));
    }

    while(1) {
       int waitflg;
       waitflg = true; 
       /* String to hold the command to run. */
       printf("Enter the command to run: ");
       if (fgets(command, MAXBUF, stdin) == NULL) {
          exit(EXIT_SUCCESS);
       }
       printf("command = %s", command);
       strcpy(tmp_input, command);
 
       int argc = 0;
       while (argc < MAXTOKENS) {
           // int cLength = strlen(command);
           // bool bWait = true;
            ret_args = sscanf(tmp_input, "%s%[^\n]", tokenArr[argc], tmp_input);
            printf("ret_args=%d, arg1=%s, arg2=%s\n", ret_args, tokenArr[argc], tmp_input); 
            if (ret_args <= 0) { break; }
            if (ret_args ==1) {
                argc+=1;
                tmp_memptr = tokenArr[argc];
                tokenArr[argc] = '\0';
                break;
            }
            argc+=1;
       }
       if (argc == 0) { continue; }
       for (i=0; i < argc; i++) {
           printf("tokenArr[%d]=%s\n", i, tokenArr[i]);
       }
       char *lasttkn = tokenArr[argc-1];
       int lasttknlen = strlen(lasttkn);
       if (strcmp(tokenArr[argc-1], "&") == 0) {
           waitflg = false;
           tokenArr[argc] = tmp_memptr;
           argc = argc-1;
           tmp_memptr = tokenArr[argc];
           tokenArr[argc] = '\0';
       } else if (lasttkn[lasttknlen-1] == '&') {
           waitflg = false;
           lasttkn[lasttknlen-1] = '\0';
           lasttknlen = lasttknlen - 1;
       } else {
           waitflg = true;
       }
       
       char cwdbuf[512]; 
       if (strcmp(tokenArr[0], "cd") == 0) {
           chdir(tokenArr[1]);
       } else if (strcmp(tokenArr[0], "secret-system-call") == 0) {
           syscall(349);
       } else if (strcmp(tokenArr[0], "pwd") == 0) {
           getcwd(cwdbuf, 512);
           printf("%s\n", cwdbuf);
       } else {
          /* Variable that will store the fork result. */
          pid_t pid;
    
          /* Perform the actual fork. */
          pid = fork();
          if (pid < 0) {
            /* Error condition. */
            fprintf(stderr, "Fork failed\n");
            return -1;
          } else if (pid == 0) {
            /* Child process. */
            printf("Child Running...cmd=%s,cmdargs=%s\n", tokenArr[0], tokenArr[1]);
            int ret;
            ret = execvp(tokenArr[0], tokenArr);
            if (ret == -1) {
               perror("execvp");
            }
          } else {
            /* Parent process. */
            int result;
            if (waitflg == false) {
              printf("not waiting\n");
            } else {
              printf("waiting\n");
              //wait(&result)`;
              waitpid(pid, &result, 0);
              printf("All done; result = %d\n", result);
            }
          }
       }
       tokenArr[argc] = tmp_memptr; 
   } 
    return 0;
}
