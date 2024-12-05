/*
This is assignment 4
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/

#ifndef PRISONEDRL_H
#define PRISONERDR_H

/*
PRISONEDRL.H
drawer semaphore prisoner functions and struct
*/

/*
Struct fot one prisoner.
A prisoner has to know their number, drawers, if they succeeded and have 
a semaphore list
*/
typedef struct prisDr{
    int num;
    int* drawers;
    int suc;
    sem_t* sem;
} prisDr;

/*
GAME DRAWER
play a game with a given prisoner strategy function with drawer based
semaphores
*/
int gameDr(void* fun (void*));

/*
PRISONER RANDOM DRAWER
execute random prisoner strategy with with drawer based
semaphores
*/
void* prisRandDr(void *prisoner);

/*
PRISONER SMART DRAWER
execute smart prisoner strategy with with drawer based
semaphores
*/
void* prisSmartDr(void *prisoner);

#endif