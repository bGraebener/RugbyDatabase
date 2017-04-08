//source file with all implementations for function that operate on a player struct

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Player.h"
#include "Menu.h"


//function that sends a single players' details to the specified outputstream
void displayPlayer(player_t* player, FILE* out) {

	//arrays to display metres, tackles and position as strings
	//values correspond with the enum values
	char tacklesArray[][25] = { "Never", "Less than three", "Less than five", "More than five" };
	char metresArray[][25] = { "None" , "Less than ten" ,"More than twenty" };
	char posArray[][25] = { "Prop", "Hooker", "Second Row", "Back Row", "Half Back", "Centre", "Winger" };

	//display all details
	fprintf(out, "\n\nPlayer Information: ");
	fprintf(out, "\nIRFU: %d ", player->irfu);
	fprintf(out, "\nName: %s %s", player->firstName, player->lastName);
	fprintf(out, "\nAge: %d", player->age);
	fprintf(out, "\nHeight: %.2f ", player->height);
	fprintf(out, "\nWeight: %.2f", player->weight);
	fprintf(out, "\nClub: %s", player->club);
	fprintf(out, "\nEmail: %s", player->email);
	fprintf(out, "\nPlayer Position: %s ", posArray[player->position]);
	fprintf(out, "\nTackles missed per game: %s", tacklesArray[player->tackles]);
	fprintf(out, "\nMetres per Game: %s\n", metresArray[player->metres]);

}

//function to retrieve unique irfu number from user
int getIrfu(player_t* head) {

	player_t* tmp;
	tmp = head;
	int irfu;
	boolean duplicate;
	int result;

	//check if irfu number is unique
	do {
		duplicate = false;

		//check for valid input
		do {
			printf("Enter Players' IRFU: ");
			result = scanf("%d", &irfu);
			fseek(stdin, 0, SEEK_END);
		} while (result < 1);

		//iterate the list and check for existing irfu number
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

	int result;

	//get players unique irfu number
	newPlayer->irfu = getIrfu(head);

	//get new player information
	printf("Enter Players' first name: ");
	scanf("%s", newPlayer->firstName);

	printf("Enter Players' last name: ");
	scanf("%s", newPlayer->lastName);

	printf("Enter Players' age: ");
	newPlayer->age = getValidInput();

	printf("Enter Players' height (cm): ");
	newPlayer->height = getValidInput();

	printf("Enter Players' weight (kg): ");
	newPlayer->weight = getValidInput();

	printf("Enter Players' club: ");
	scanf("%s", newPlayer->club);

	printf("Enter Players' email: ");
	strcpy(newPlayer->email, getValidEmail());

	//get position, tackles and metres as enums
	int pos = getPlayerPosition();
	newPlayer->position = pos - 1;

	int tackles = getPlayerTackles();
	newPlayer->tackles = tackles - 1;

	int metres = getPlayerMetres();
	newPlayer->metres = metres - 1;

	return newPlayer;
}

//function that checks for valid integer input and returns it
int getValidInput() {
	int input;
	int result;

	result = scanf("%f", &input);
	while (result < 1) {
		fseek(stdin, 0, SEEK_END);
		printf("\nInvalid input! Try again!");
		printf("\nEnter Value: ");
		result = scanf("%f", &input);
	}
	return input;
}


//function that checks and return a valid email
char* getValidEmail() {
		
	int atIndex;
	int dotComIndex;
	int emailEnd;

	char email[35];
	scanf("%s", email);

	//the position where the '.com' should start to be last 
	emailEnd = strlen(email) - strlen(".com") -1;

	//get new input while email not contains a '.com' or '@'
	while (strstr(email, "@") == NULL || strstr(email, ".com") == NULL) {
		printf("\nInvalid Email! Email must contain '@' and '.com'");
		printf("\nEnter Players' email: ");
		scanf("%s", email);
	}

	//store position of '@' and '.com'
	atIndex = strstr(email, "@") - email;
	dotComIndex = strstr(email, ".com") - email;

	//get new input while the '@' is either in first position or after the '.com' 
	//or while '.com' is not at the end of the email 
	while (dotComIndex < atIndex || atIndex == 0 || dotComIndex < emailEnd) {
		printf("\nInvalid Email! '@' can't be first character and '.com' has to be last");
		printf("\nEnter Players' email: ");
		scanf("%s", email);

		emailEnd = strlen(email) - 1 - strlen(".com");
		atIndex = strstr(email, "@") - email;
		dotComIndex = strstr(email, ".com") - email;
	}

	return email;
}
