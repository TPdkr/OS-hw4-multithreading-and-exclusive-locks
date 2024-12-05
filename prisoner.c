/*
This is assignment 4
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#include <stdio.h>
#include <semaphore.h>
#include "utils.h"
#include "prisonerGl.h"
#include "prisonerDr.h"

int main(int argc, char* argv[]){
    flags flag;
    //we get the otions
    getOptions(argc,argv,&flag);
    //we start the games
    startGame(gameGl,prisSmartGl,"smart_global",flag);
    startGame(gameDr,prisSmartDr,"smart_drawer",flag);
    startGame(gameGl,prisRandGl,"random_global",flag);
    startGame(gameDr,prisRandDr,"random_drawer",flag);
    return 0;
}