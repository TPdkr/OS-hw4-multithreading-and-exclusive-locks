/*
This is assignment 4
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include "utils.h"
#include "prisonerGl.h"

//GET POSITIVE INT-------------------------------------------------------------
void getPosInt(int* num, char flag,char inp[]){
    int suc=sscanf(inp, "%d", num);
    //is the arguemnt int check
    if (suc!=1){
        fprintf(stderr, "prisoner: invalid number %s for -%c option\n", inp,flag);
        exit(1);
    }
    //invalid int check
    if(*num<=0){
        fprintf(stderr,"prisoner: value %d for -%c option should be >= 1\n", *num,flag);
        exit(1);
    }
}

//GET UNSIGNED INT-------------------------------------------------------------
void getUnsInt(int* num, char flag,char inp[]){
    int suc=sscanf(inp, "%d", num);
    //is the arguemnt int check
    if (suc!=1){
        fprintf(stderr, "prisoner: invalid number %s for -%c option\n", inp,flag);
        exit(1);
    }
    //invalid int check
    if(*num<0){
        fprintf(stderr,"prisoner: value %d for -%c option should be >= 0\n", *num,flag);
        exit(1);
    }
}
//GET OPTIONS------------------------------------------------------------------
void getOptions( int argc, char* argv[], flags* flag){
    //the argument position
    int argPos=1;
    //we set default values
    flag->seed=time(NULL);
    flag->gamesNum=100;
    int opt;
    //we use getopt for options
    while((opt = getopt(argc, argv, ":n:s:"))!=-1){
        switch(opt){
            case 'n':
                getPosInt(&flag->gamesNum,'n',optarg);
                argPos+=2;
                break;
            case 's':
                getUnsInt(&flag->seed,'s',optarg);
                argPos+=2;
                break;
            case ':'://nothing to be done but call an error
            case '?'://unknown flag meaning invalid input
                fprintf(stderr,"prisoner: invalid option '%c'\n", opt);
                exit(1);
                break;
        }
    }
    //is there still something left? ERROR in input
    if(argv[argPos]!=NULL){
        fprintf(stderr,"prisoner: too many arguments supplied\n");
        exit(EXIT_FAILURE);
    }
    //we initiate srand
    srand(flag->seed);
}

//GENERATE DRAWERS-------------------------------------------------------------
int* genDrawers(int num){
    //we allocate memory
    int* drawers = (int*) malloc(num*sizeof(int));
    if(drawers == NULL){
        fprintf(stderr,"prisoner: memory allocation failure\n");
        exit(EXIT_FAILURE);
    }
     //we put -1 in the array
    for(int i=0; i<num;i++){
        drawers[i]=-1;
    } 
    //we start putting numbers
    for(int i=0;i<num;i++){
        int spot = rand()%(num-i);
        int passed=0;
        for(int j=0;j<num;j++){
            //found a spot
            if (passed==spot && drawers[j]==-1){
                drawers[j]=i;
                break;
            //have to keep searching
            } else if (drawers[j]==-1){
                passed++;
            }
        }
    }
    return drawers;
}

//START A GAME TEST------------------------------------------------------------
void startGame(int gameX(void* fun0 (void*)), void* fun (void*), char* name, flags flag){
    clock_t t1, t2;//for tracking time
    double timeSpent=0, avgTime;//for storing time
    int won=0;//how many wins?

    //we measure time and run the games
    for(int i=0; i<flag.gamesNum;i++){
        t1 = clock();
        won+=gameX(fun);
        t2 = clock();
        timeSpent+=((double) t2 - (double) t1) / CLOCKS_PER_SEC * 1000;

    }

    //avergae time and percentage
    avgTime = timeSpent/flag.gamesNum;
    float percnt = (float) won / (float) flag.gamesNum;

    //output
    printf("%s     %d/%d wins/games = %.2f%%",name,won,flag.gamesNum, percnt);
    printf("     %.3f/%d ms = %.3f ms\n", timeSpent, flag.gamesNum, avgTime);
}