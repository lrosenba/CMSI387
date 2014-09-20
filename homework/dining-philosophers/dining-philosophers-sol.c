//This program works only on linux because OS X only supports named semaphores.
//This program follows Tannenbaum's algorithm for the solution.

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#define TOTAL_PHILOSOPHERS 5
#define LEFT(i) ( ((i) + 1) % TOTAL_PHILOSOPHERS )
#define RIGHT(i) ( ((i) - 1 + TOTAL_PHILOSOPHERS) % TOTAL_PHILOSOPHERS )
typedef enum {THINKING, EATING, HUNGRY} state;

pthread_t phil_threads[TOTAL_PHILOSOPHERS];
int phil_ids[TOTAL_PHILOSOPHERS];
sem_t phil_sem[TOTAL_PHILOSOPHERS];
sem_t mutex;

//a struct is created for each philosopher.
typedef struct {
    int id;
    int eatCount;
    int otherCount;
    //int threadId;
    //state left;
    //state right;
    state pState;
} Phil;

Phil phils[TOTAL_PHILOSOPHERS];

//This method tests whether a philosopher is able to eat. 
void test(int id) {
    //printf("philosopher %d being tested\n", id);
    if (phils[id].pState == HUNGRY && phils[LEFT(id)].pState != EATING && phils[RIGHT(id)].pState != EATING) {
         phils[id].pState = EATING;
         sem_post(&phil_sem[id]);
    }
    int i;
    for (i=0; i < TOTAL_PHILOSOPHERS; i++) {
         printf("Philosopher[%d] is %s, ", i, (phils[i].pState==THINKING)?"THINKING" : (phils[i].pState==EATING)?"EATING":"HUNGRY" );
         if (phils[i].pState == EATING) {
             phils[i].eatCount = phils[i].eatCount + 1;
         } else {
             phils[i].otherCount = phils[i].otherCount + 1;
         }
    }
    for (i=0; i < TOTAL_PHILOSOPHERS; i++) {
        assert(phils[i].pState != EATING || phils[LEFT(i)].pState != EATING);
    }
    printf("\n");
 }

void pickUpSticks(int id) {
    sem_wait(&mutex);
    phils[id].pState = HUNGRY;
    test(id);
    sem_post(&mutex);
    sem_wait(&phil_sem[id]);
}

void putDownSticks(int id) {
    sem_wait(&mutex);
    phils[id].pState = THINKING;
    test(LEFT(id));
    test(RIGHT(id));
    sem_post(&mutex);
    if (phils[id].eatCount + phils[id].otherCount >= 1000) {
        pthread_exit(NULL);
    }
}

// setting the beginning state of the philosophers.
void* seating(void* idptr) {
    int *phid = idptr;
    int id = *phid;
    while (1) {
        phils[id].pState = THINKING;
        usleep(rand() % 100);
        pickUpSticks(id);
        usleep(rand() % 100);
        putDownSticks(id);
    }               
}

int main(int argc, char** argv) {

    if (sem_init(&mutex, 0, 1)) {
         perror("semaphore ");
         printf("Could not initialize mutex semaphore\n");
    }

    int i;
    for (i=0; i<TOTAL_PHILOSOPHERS; i++) {
        if (sem_init(&phil_sem[i], 0, 1)) {
            printf("Could not initialize semaphore %d\n",i);
            perror("semaphore ");
        }
    }
 
    for (i=0; i<TOTAL_PHILOSOPHERS; i++) {
        phils[i].id = i;
        phils[i].eatCount = 0;
        phils[i].otherCount = 0;
        if (pthread_create(&phil_threads[i],NULL,&seating,&phils[i].id)){
            printf("Could not create thread %d\n",i);
        }
    }
    for (i=0; i<TOTAL_PHILOSOPHERS; i++){ 
        if (pthread_join(phil_threads[i],NULL)!=0){
            printf("problem with thread during join operation. %d\n",i);
        }
    }
    for (i=0; i<TOTAL_PHILOSOPHERS; i++){
        printf("philosopher%d ate %d times ", i, (phils[i].eatCount));
    }    
    printf("\n");

    return 0;
}
