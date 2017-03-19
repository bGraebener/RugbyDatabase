#pragma once

#include "Player.h"

//node struct for the linked list
typedef struct node {
	struct player_t* player;
	struct node* next;
}node_t;

//function prototypes
void populateList(node_t** head);
void addFirst(node_t**, player_t*);
void insertSorted(node_t**, player_t*);
int findLocation(node_t*, int);
void printToFile(node_t*);
int findPlayer(node_t*);