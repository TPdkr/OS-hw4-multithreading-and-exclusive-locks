# Assignment 4
## Submitted by Timofei Podkorytov
for operating systems course in fall 2024

## Compiling: Makefile
The following make commands are available:
```
$ make prisoner
```
This compiles all files into prisoner executable that accepts user input.
## Running:
Runs the main function and produces the avergae times for all scenarious:

```./prisoner``` - no input can be given, but also takes -n int and
-s int options

## Files:
- Makefile
- README.md
- prisoner.c
- utils.h
- utils.c
- prisonerGl.h
- prisonerGl.c
- prisonerDr.h
- prisonerDr.c

Makefile provides make commands. README gives the description of the 
homework submission.

The file prisoner.c has the main function, where all the other function calls
are made. There we first process the options and then we start the games.

Utils files have functions for input and things like creating the drawers and
running the game. So, things that are used in global and local semaphore 
scenarios can be accessed in both files.

PrisonerGl header and c file give function for global semaphores like starting
a game and smart and random prisoners.

PrisonerDr files contain the functions for drawer based semaphores. There all 
the prisoners execute concurrently, but only one can open each drawer.

## Output
I ran the following command:
```
$ ./prisoner -n 500
```
The terminal displayed:
```
random_global     0/500 wins/games = 0.00%     4039.200/500 ms = 8.078 ms
random_drawer     0/500 wins/games = 0.00%     3846.310/500 ms = 7.693 ms
smart_global     137/500 wins/games = 0.27%     3437.331/500 ms = 6.875 ms
smart_drawer     156/500 wins/games = 0.31%     1654.734/500 ms = 3.309 ms
```
As we can see drawer based semaphores and parallel execution make it run faster.
 The percentage of success matches the expected level of around 30%.