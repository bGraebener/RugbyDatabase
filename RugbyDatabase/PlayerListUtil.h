//header file for list functions that don't change the linked list of players
#pragma once
#include "Player.h"

//function prototype declarations

//primary functions
void displayPlayers(player_t*);
int displayDetails(player_t*);
void displayInOrder(player_t*);
void generateStats(player_t*);

//utility functions
int size(player_t*);
int searchByIrfu(player_t*, int);
int searchByName(player_t*, char*, char*);
int findLocation(player_t*, int, sortField);
