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
#include "prisonerDr.h"
#include "utils.h"

//GAME DRAWER------------------------------------------------------------------
int gameDr(void* fun (void*)){
    int win=1;//did we win?
    int num=100;//number of prisoners
    pthread_t tid[num];//thread ids
    prisDr prisoners[num];//prisoners
    int* drawers=genDrawers(num);//drawers
    sem_t sem[100];//semaphores for each drawer

    //we initate all semaphores
    for(int i=0;i<num;i++){
        (void) sem_init(&sem[i],0,1);
    }
    
    for(int i=0;i<num;i++){
        //we set prisoner values
        prisoners[i].num=i;
        prisoners[i].drawers=drawers;
        prisoners[i].sem = sem;
        prisoners[i].suc=0;
        //we create thread
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
        //did we lose?
        if(prisoners[i].suc==0){
            win=0;
        }
    }
    //free memory
    free(drawers);
    return win;

}

//PRISONER RANDOM DRAWER-------------------------------------------------------
void* prisRandDr(void *prisoner){
    prisDr* pris = (prisDr *) prisoner;   
    for(int i=0;i<50;i++){
        int spot;//the random drawer
        spot = rand()%100;
        //lower the semaphore
        (void) sem_wait(&pris->sem[spot]);
        //we check a random drawer
        if(pris->drawers[spot]==pris->num){
            pris->suc=1;
            (void) sem_post(&pris->sem[spot]);
            break;
        }
        //raise the semaphore
        (void) sem_post(&pris->sem[spot]);
    }
    return NULL;

}

//PRISONER SMART DRAWER--------------------------------------------------------
void* prisSmartDr(void *prisoner){
    prisDr* pris = (prisDr *) prisoner;
    //first one is our number
    int cur = pris->num;
    for(int i=0;i<50;i++){
        int semPlace=cur;
        //lower the semaphore
        (void) sem_wait(&pris->sem[semPlace]);
        //we check the drawer
        if(pris->drawers[cur]==pris->num){
            pris->suc=1;
            //raise the semaphore if found because exiting loop
            (void) sem_post(&pris->sem[semPlace]);
            break;
            
        }
        cur=pris->drawers[cur];
        //raise the semaphore
        (void) sem_post(&pris->sem[semPlace]);
    }
    return NULL;

}