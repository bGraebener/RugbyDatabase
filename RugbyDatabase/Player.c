//source file with all implementations for function that operate on a player struct

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Player.h"


//function that displays a sinlge players' details
void displayPlayer(player_t* player) {

	//arrays to display metres, tackles and position as strings
	//values correspond with the enum values
	char tacklesArray[][25] = { "Never", "Less than three", "Less than five", "More than five" };
	char metresArray[][25] = { "None" , "Less than ten" ,"More than twenty" };
	char posArray[][25] = { "PROP", "HOOKER", "SECOND ROW", "BACK ROW", "HALF BACK", "CENTRE", "WINGER" };

	//display all details
	printf("\n\nPlayer Stats: ");
	printf("\nPlayer IRFU: %d ", player->irfu);
	printf("\nPlayer Name: %s %s", player->firstName, player->lastName);
	printf("\nPlayer Age: %d", player->age);
	printf("\nPlayer Height: %.2f ", player->height);
	printf("\nPlayer Weight: %.2f", player->weight);
	printf("\nPlayer Club: %s", player->club);
	printf("\nPlayers Email: %s", player->email);
	printf("\nPlayer Position: %s ", posArray[player->position]);
	printf("\nTackles missed per game: %s", tacklesArray[player->tackles]);
	printf("\nMetres per Game: %s", metresArray[player->metres]);

}


//function to retrieve unique irfu number from user
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

	player_t* newPlayer = (player_t*)malloc(sizeof(player_t));
	player_t* tmp;
	tmp = head;

	//get players unique irfu number
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
	printf("Enter Players' email: ");
	scanf("%s", newPlayer->email);

	while (strstr(newPlayer->email, "@") == NULL || strstr(newPlayer->email, ".com") == NULL) {
		printf("\nInvalid Email! must contain '@' and '.com'");
		printf("\nEnter Players' email: ");
		scanf("%s", newPlayer->email);
	}

	//get position, tackles and metres as enums
	int pos = getPlayerPosition();
	newPlayer->position = pos - 1;

	int tackles = getPlayerTackles();
	newPlayer->tackles = tackles - 1;

	int metres = getPlayerMetres();
	newPlayer->metres = metres - 1;

	return newPlayer;
}


