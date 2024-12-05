/*
This is assignment 4
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#ifndef PRISONERGL_H
#define PRISONERGL_H

/*
PRISONERGL.H
global semaphore prisoner functions and struct
*/

/*
Struct fot one prisoner.
A prisoner has to know their number, drawers, if they succeeded and have 
a semaphore
*/
typedef struct prisGl{
    int num;
    int* drawers;
    int suc;
    sem_t *sem;
} prisGl;

/*
GAME GLOBAL
play a game with a given prisoner strategy function with global semaphore
*/
int gameGl(void* fun (void*));

/*
PRISONER RANDOM GLOBAL
execute random prisoner strategy with global semaphore
*/
void* prisRandGl(void *prisoner);

/*
PRISONER SMART GLOBAL
execute smart prisoner strategy with global semaphore
*/
void* prisSmartGl(void *prisoner);
#endif