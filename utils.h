/*
This is assignment 4
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/

#ifndef UTILS_H
#define UTILS_H

/*
UTILS.H
here are functions for input and common for different kinds of semaphores
*/

/*
STRUCT FLAGS
Here i defined a trcut for storing flags that are passed

int seed - random generation seed
int gamesNum - number of games
*/
typedef struct flags{
    int seed;
    int gamesNum;
} flags;

/*
GET POSITIVE INT
This function is used for user input to get a positive integer
*/
void getPosInt(int* num, char flag, char inp[]);
/*
GET UNSIGNED INT
This function is used for user input to get a unsigned integer
*/
void getUnsInt(int* num, char flag,char inp[]);
/*
GET OPTIONS
This function gets the flags and handles the options. It changes the variables
in accordance with the choice of the user.
char* argv-argument list
int argc-number of arguments
flags flag-a pointer to where the input flags will be stored
*/
void getOptions(int argc, char* argv[], flags* flag);

/*
GENERATE DRAWERS
num-the number of drawers to generate
*/
int* genDrawers(int num);

/*
START A GAME TEST
we give it a function for game type global/drawer and a prisoner function as well as
the name to be printed and flags from input
*/
void startGame(int gameX(void* fun0 (void*)), void* fun (void*), char* name, flags flag);
#endif