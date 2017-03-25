//header file for list functions that don't change the linked list of players
#pragma once
#include "Player.h"

//function prototype declarations
int size(player_t*);
int searchForPlayer(player_t*);
int searchByIrfu(player_t*, int);
int searchByName(player_t*, char*, char*);
void displayPlayers(player_t*);
void displayDetails(player_t*);
void generateStats(player_t*);
int getPlayerPosition();
int getPlayerMetres();
int getPlayerTackles();

//TODO
void displayInOrder(player_t*);