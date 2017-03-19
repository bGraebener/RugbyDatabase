#pragma once
#include "Player.h"
#include "Main.h"

//custom boolean type
typedef int boolean;
#define true 1
#define false 0

//function prototypes
boolean displayStartMenu();
int displayMainMenu();
player_t* addPlayer(node_t*);
void displayPlayers(node_t*);
void displayDetails(node_t*, int);
void updatePlayer(node_t*, int);
void deletePlayer(node_t*, int);
void generateStats(node_t*);
int getPlayerPosition();
int getPlayerMetres();
int getPlayerTackles();