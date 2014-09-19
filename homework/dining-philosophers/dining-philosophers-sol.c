#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define TOTAL_PHILOSOPHERS 5
#define LEFT(i) ( ((i) + 1) % TOTAL_PHILOSOPHERS )
#define RIGHT(i) ( ((i) - 1 + TOTAL_PHILOSOPHERS) % TOTAL_PHILOSOPHERS )
typedef enum {THINKING, EATING, HUNGRY} state;

pthread_t phil_threads[TOTAL_PHILOSOPHERS];
int phil_ids[TOTAL_PHILOSOPHERS];
sem_t * phil_sem[TOTAL_PHILOSOPHERS];
sem_t * mutex;

typedef struct {
    int id;
    //int threadId;
    //state left;
    //state right;
    state pState;
} Phil;

Phil phils[TOTAL_PHILOSOPHERS];

void test(int id) {
    printf("philosopher %d being tested\n", id);
    if (phils[id].pState == HUNGRY && phils[LEFT(id)].pState != EATING && phils[RIGHT(id)].pState != EATING) {
         phils[id].pState = EATING;
         //sem_post(phil_sem[id]);
    }
    int i;
    for (i=0; i < 5; i++) {
         printf("state[%d]=%s, ", i, (phils[i].pState==THINKING)?"THINKING" : (phils[i].pState==EATING)?"EATING":"HUNGRY" );
    }
    printf("\n");
    if (phils[id].pState == EATING) {
        sleep(rand() % 4);
    }
 }

void pickUpSticks(int id) {
    printf("philosopher %d is picking up sticks.mutex= %d\n", id, (int) mutex);
    sem_wait(mutex);
    printf("post: philosopher %d is picking up sticks\n", id);
    phils[id].pState = HUNGRY;
    test(id);
    sem_post(mutex);
    // printf("id:%d ", p.x);
    //sem_wait(phil_sem[id]);

}

void putDownSticks(int id) {
    sem_wait(mutex);
    phils[id].pState = THINKING;
    test(LEFT(id));
    test(RIGHT(id));
    sem_post(mutex);
}

// setting the beginning state of the philosophers.
void* seating(void* idptr) {
    int *phid = idptr;
    int id = *phid;
    printf("philosopher %d now sitting\n", id);
    while (1) {
        phils[id].pState = THINKING;
        sleep(rand() % 5);
        pickUpSticks(id);
        sleep(rand() % 5);
        putDownSticks(id);
    }               
}

/*void *printer(void *arg) {
    printf("Starting thread\n");
    int wait = (int)arg;
    while(1) {
        time_t result = time(NULL);
        sleep(wait);
        printf("thread id = %d time = %s\n", (int)pthread_self(), asctime(localtime(&result)));
    }
    printf("Ending thread\n");
}*/

int main(int argc, char** argv) {
    printf("pre- mutex=%d\n",(int) mutex);

    mutex = sem_open("/Users/list/mutex", O_CREAT, 0644, 1);
    sem_close(mutex);
    mutex = sem_open("/Users/list/mutex", O_CREAT, 0644, 1);
    if (mutex == SEM_FAILED) {
         perror("semaphore ");
         printf("Could not initialize mutex semaphore\n");
    }
    printf("mutex=%d\n",(int) mutex);

    int i;
    char sem_name[512];
    for (i=0; i<TOTAL_PHILOSOPHERS; i++) {
        sprintf(sem_name, "/tmp/phil_sem%d", i);
        phil_sem[i] = sem_open(sem_name, O_CREAT, 0644, 1);
        if (phil_sem[i] == SEM_FAILED) {
        //if (sem_init(&phil_sem[i], 0, 1)) {
            printf("Could not initialize semaphore %d\n",i);
            perror("semaphore ");
        }
    }
    printf("creating threads\n");    
 
    for (i=0; i<TOTAL_PHILOSOPHERS; i++) {
        phils[i].id = i;
        if (pthread_create(&phil_threads[i],NULL,&seating,&phils[i].id)){
            printf("Could not create thread %d\n",i);
        }
    }
    for (i=0; i<TOTAL_PHILOSOPHERS; i++){ 
        if (pthread_join(phil_threads[i],NULL)!=0){
            printf("problem with thread during join operation. %d\n",i);
        }
    }

    return 0;
}
