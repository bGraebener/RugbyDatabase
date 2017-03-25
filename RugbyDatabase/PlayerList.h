//header file for functions that change the state of the linked list of players

#pragma once

#include "Player.h"
#include "Menu.h"

//function prototypes for the list of players

//primary functions
void updatePlayer(player_t**);
void deletePlayer(player_t**, int);
void insertSorted(player_t**, player_t*);

//utility functions
void populateList(player_t** head);
void addFirst(player_t**, player_t*);
void deleteFirst(player_t**);
void freeLinkedList(player_t*);