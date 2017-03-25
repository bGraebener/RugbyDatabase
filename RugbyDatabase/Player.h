#pragma once
//header file for a player 
//defines the player struct and functions that perform operations on a single player

//custom boolean type
typedef int boolean;
#define true 1
#define false 0

//enums for position, tackles and metres
typedef enum {
	PROP, HOOKER, SECOND_ROW, BACK_ROW, HALF_BACK, CENTRE, WINGER
}position;

typedef enum {
	NEVER, LESS_THREE, LESS_FIVE, MORE_FIVE
}tackles_missed;

typedef enum {
	NONE, LESS_TEN, LESS_TWENTY, MORE_TWENTY 
}metres;

//enum to specify a field by which a list can be sorted
typedef enum {
	IRFU, HEIGHT
}sortField;

//public player struct
typedef struct player_t{

	int irfu;
	char firstName[25];
	char lastName[25];
	int age;
	float height;
	float weight;
	char club[25];
	char email[35];
	enum position position;
	enum tackles_missed tackles;
	enum metres metres;

	struct player_t* next;

}player_t;

//function prototypes for player struct
void displayPlayer(player_t*, FILE*);
player_t* createPlayer(player_t*);
int getIrfu(player_t* head);

