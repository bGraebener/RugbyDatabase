//header file for list functions that don't change the linked list of players
#pragma once
#include <stdio.h>
#include "Player.h"

//function prototype declarations

//primary functions
void displayPlayers(player_t*, FILE*);
int displayDetails(player_t*);
void displayInOrder(player_t*);
void generateStats(player_t*, FILE*);
void generateStatsByPosition(player_t*, FILE*);
void generateStatsByWeight(player_t*, FILE*);

//utility functions
int size(player_t*);
int searchByIrfu(player_t*, int);
int searchByName(player_t*, char*, char*);
int findLocation(player_t*, int, sortField);
