//header file for list functions that don't change the linked list of players

#ifndef LIST_UTIL_H
#define LIST_UTIL_H

#include <stdio.h>
#include "Player.h"

//struct to help generate the statistics report

typedef struct
{
	int amount;

	int tacklesArray[4];
	int metresArray[4];

}stats;


//function prototype declarations

//primary functions
void displayPlayers(player_t*, FILE*);
int displayDetails(player_t*);
void displayInOrder(player_t*);
void generateStats(player_t*, FILE*);

//utility functions
int size(player_t*);
int searchByIrfu(player_t*, int);
int searchByName(player_t*, char*, char*);
int findLocation(player_t*, int, sortField);
void displayStats(stats* group, FILE* out);
void generateStatsByPosition(player_t*, FILE*);
void generateStatsByWeight(player_t*, FILE*);

#endif // !LIST_UTIL.H
