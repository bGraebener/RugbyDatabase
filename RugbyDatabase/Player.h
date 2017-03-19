#pragma once


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

}player_t;

//function prototypes for player struct
void displayPlayer(player_t*);
const char* findPosition(position);
const char* findTackles(tackles_missed);
const char* findMetres(metres);
