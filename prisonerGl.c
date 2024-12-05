/*
This is assignment 4
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include "prisonerGl.h"
#include "utils.h"

//GAME GLOBAL------------------------------------------------------------------
int gameGl(void* fun (void*)){
    int win=1;//did we win?
    int num=100;//number of prisoners
    sem_t sem;//semaphore
    pthread_t tid[num];//thread ids
    prisGl prisoners[num];//prisoners
    int* drawers=genDrawers(num);//drawers

    (void) sem_init(&sem,0,1);//initiate semaphore
    for(int i=0;i<num;i++){
        //we set prisoner values
        prisoners[i].num=i;
        prisoners[i].drawers=drawers;
        prisoners[i].sem=&sem;
        prisoners[i].suc=0;
        //create a thread
        int rc = pthread_create(&tid[i], NULL, fun, &prisoners[i]);
        if(rc != 0){
			fprintf(stderr, "prisoner: pthread_create failed\n");
			exit(EXIT_FAILURE);
		}
    }
    for(int i=0;i<num;i++){
        //joining all threads and waiting for correctness
        int rc = pthread_join(tid[i], NULL);
		if(rc!=0){
			fprintf(stderr, "prisoner: pthread_join failed\n");
			exit(EXIT_FAILURE);
		}
        //check if we lost
        if(prisoners[i].suc==0){
            win=0;
        }
    }
    //free memory
    free(drawers);
    return win;
}

//PRISONER RANDOM GLOBAL-------------------------------------------------------
void* prisRandGl(void *prisoner){
    prisGl* pris = (prisGl *) prisoner;
    //lower the semaphore
    (void) sem_wait(pris->sem);
    
    for(int i=0;i<50;i++){
        int spot;//whcih box we check
        spot = rand()%100;
        //we check a random drawer
        if(pris->drawers[spot]==pris->num){
            pris->suc=1;
            break;
        }
    }
    //raise the semaphore
    (void) sem_post(pris->sem);
    return NULL;
}

//PRISONER SMART GLOBAL--------------------------------------------------------
void* prisSmartGl(void *prisoner){
    prisGl* pris = (prisGl *) prisoner;
    //lower the semaphore
    (void) sem_wait(pris->sem);
    //first one is our number
    int cur = pris->num;
    for(int i=0;i<50;i++){
        //we check the drawer
        if(pris->drawers[cur]==pris->num){
            pris->suc=1;
            break;
        }
        cur=pris->drawers[cur];
    }
    //raise the semaphore
    (void) sem_post(pris->sem);
    return NULL;
}