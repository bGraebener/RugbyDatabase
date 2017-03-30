//header file for functions that change the state of the linked list of players

#ifndef LIST_H
#define LIST_H

#include "Player.h"
#include "Menu.h"

//function prototypes for the list of players

//primary functions
void updatePlayer(player_t**);
void deletePlayer(player_t**);
void insertSorted(player_t**, player_t*);

//utility functions
void populateList(player_t** head);
void addFirst(player_t**, player_t*);
void deleteFirst(player_t**);
void freeLinkedList(player_t*);
#endif // !LIST_H
