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



int getIrfu(player_t* head) {
		
	player_t* tmp;
	tmp = head;

	int irfu;
	boolean duplicate;

	//check if irfu number is unique
	do {
		duplicate = false;
		printf("Enter Players' IRFU: ");
		scanf("%d", &irfu);

		for (; tmp != NULL; tmp = tmp->next) {
			if (tmp->irfu == irfu) {
				duplicate = true;
				printf("\nIRFU Number already exists, try again!\n");
				break;
			}
		}
	} while (duplicate);

	return irfu;
}

//function that gets details of a new player from user input
player_t* createPlayer(player_t* head) {

	player_t* newPlayer = (player_t*) malloc(sizeof(player_t));
	player_t* tmp;
	tmp = head;

	boolean at;
	boolean dot;
	
	newPlayer->irfu = getIrfu(head);

	//get new player information
	printf("Enter Players' first name: ");
	scanf("%s", newPlayer->firstName);

	printf("Enter Players' last name: ");
	scanf("%s", newPlayer->lastName);

	printf("Enter Players' age: ");
	scanf("%d", &newPlayer->age);

	printf("Enter Players' height: ");
	scanf("%f", &newPlayer->height);

	printf("Enter Players' weight: ");
	scanf("%f", &newPlayer->weight);

	printf("Enter Players' club: ");
	scanf("%s", newPlayer->club);

	//check if email has both an '@' an a '.com' 
	do {
		printf("Enter Players' email: ");
		scanf("%s", newPlayer->email);
	
	} while (strstr(newPlayer->email, "@") == NULL || strstr(newPlayer->email, ".com") == NULL);

	
	//get position, tackles and metres as enums
	int pos = getPlayerPosition();
	newPlayer->position = pos - 1;

	int tackles = getPlayerTackles();
	newPlayer->tackles = tackles - 1;

	int metres = getPlayerMetres();
	newPlayer->metres = metres - 1;

	return newPlayer;
}


// convenience function for prompting for players metres per game
int getPlayerMetres() {

	printf("\nEnter metres player makes per game: ");
	printf("\n1 - None");
	printf("\n2 - Less than 10");
	printf("\n3 - Less than 20");
	printf("\n4 - More than 20");
	printf("\nPosition: ");

	int metres;
	scanf("%d", &metres);

	return metres;
}


// convenience function for prompting for players tackles per game
int getPlayerTackles() {

	printf("\nEnter tackles a player misses per game: ");
	printf("\n1 - Never");
	printf("\n2 - Less than 3");
	printf("\n3 - Less than 5");
	printf("\n4 - More than 5");
	printf("\nPosition: ");

	int tackles;
	scanf("%d", &tackles);

	return tackles;
}

// convenience function for prompting for players position
int getPlayerPosition() {

	printf("\nEnter Players' position: ");
	printf("\n1 - Prop");
	printf("\n2 - Hooker");
	printf("\n3 - Second Row");
	printf("\n4 - Back Row");
	printf("\n5 - Half Back");
	printf("\n6 - Centre");
	printf("\n7 - Winger/Full Back");
	printf("\nPosition: ");

	int pos;
	scanf("%d", &pos);

	return pos;
}


//function to find a new players position inside the linked list by order of irfu number
int findLocation(player_t* head, int irfu) {

	//temporary head node copy
	player_t* tmp = head;
	int position = 0;

	//determine correct position by checking irfu number against existing records
	while (tmp->irfu < irfu) {
		position++;
		tmp = tmp->next;

		if (tmp == NULL) {
			break;
		}
	}
	return position;
}

