#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Player.h"

//function that displays a sinlge players' details
void displayPlayer(player_t* player) {

	//translate position, tackles and metres enums into strings for display
	const char* pos = findPosition(player->position);
	const char* metres = findMetres(player->metres);
	const char* tackles = findTackles(player->tackles);

	//display all details
	printf("\n\nPlayer Stats: ");
	printf("\nPlayer IRFU: %d ", player->irfu);
	printf("\nPlayer Name: %s %s", player->firstName, player->lastName);
	printf("\nPlayer Age: %d", player->age);
	printf("\nPlayer height: %.2f ", player->height);
	printf("\nPlayer weight: %.2f", player->weight);
	printf("\nClub: %s", player->club);
	printf("\nPlayers Email: %s", player->email);
	printf("\nPlayer position: %s ", pos);
	printf("\nTackles missed per game: %s", tackles);
	printf("\nMetres per Game: %s", metres);

}

//function that translates the players metres enum value to a string for display purposes
const char* findMetres(metres metresPerGame) {
	
	char* metres = (char*)malloc(sizeof(char)*25);

	switch (metresPerGame)
	{
	case NONE:
		strcpy(metres, "None");
		break;
	case LESS_TEN:
		strcpy(metres, "Less than ten");
		break; 
	case LESS_TWENTY: 
		strcpy(metres, "Les than twenty");
		break; 
	case MORE_TWENTY:
		strcpy(metres, "More than twenty");
		break;
	default:
		break;
	}
	return metres;
}

//function that translates the players tackles enum value to a string for display purposes
const char* findTackles(tackles_missed tackles) {

	char* tacklesMiss = (char*)malloc(sizeof(char)*25);

	switch (tackles) {
	case NEVER:
		strcpy(tacklesMiss, "Never");
		break;
	case LESS_THREE:
		strcpy(tacklesMiss, "Less than three");
		break;
	case LESS_FIVE:
		strcpy(tacklesMiss, "Less than five");
		break;
	case MORE_FIVE:
		strcpy(tacklesMiss, "More than five");
		break;
	default:
		break;
	}

	return tacklesMiss;
}

//function that translates the players position enum value to a string for display purposes
const char* findPosition(position position) {

	char* pos = (char*)malloc(sizeof(char)*25);

	switch (position)
	{
	case CENTRE:
		strcpy(pos, "Centre");
		break;
	case WINGER:
		strcpy(pos, "Winger");
		break;
	case PROP:
		strcpy(pos, "Prop");
		break;
	case HOOKER:
		strcpy(pos, "Hooker");
		break;
	case SECOND_ROW:
		strcpy(pos, "Second Row");
		break;
	case BACK_ROW:
		strcpy(pos, "Back Row");
		break;
	case HALF_BACK:
		strcpy(pos, "Half Back");
		break;
	default:
		break;
	}

	return pos;

}