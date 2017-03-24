//header file for functions that change the state of the linked list of players

#pragma once

#include "Player.h"
#include "Menu.h"

//function prototypes for the list of players
void updatePlayer(player_t*);
void deletePlayer(player_t**, int);
void populateList(player_t** head);
void addFirst(player_t**, player_t*);
void insertSorted(player_t**, player_t*);
void deleteFirst(player_t**);
