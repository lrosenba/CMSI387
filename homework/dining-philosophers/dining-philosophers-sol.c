#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

void *printer(void *arg) {
    printf("Starting thread\n");
    int wait = (int)arg;
    while(1) {
        time_t result = time(NULL);
        sleep(wait);
        printf("thread id = %d time = %s\n", (int)pthread_self(), asctime(localtime(&result)));
    }
    printf("Ending thread\n");
}

int main(int argc, char** argv) {
    printf("before threads are created\n");

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, printer, (void *)4);
    pthread_create(&thread2, NULL, printer, (void *)6);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
