#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "Menu.h"
#include "Player.h"


//login struct
typedef struct {
	char username[25];
	char password[6];
}login;


//entry point to the application 
//reads the login records from a file and 
//checks user credentials against the login records
boolean displayStartMenu() {

	//attempt to open the login records file
	FILE* loginFile = fopen("login.txt", "r");

	//array to store the login records
	login* records = (login*)malloc(sizeof(login) * 3);

	//temporary storage of  username and password 
	char username[15];
	char password[6];

	//read in username and password records from file
	if (loginFile != NULL) {
		for (int i = 0; i < 3; i++) {
			fscanf(loginFile, "%s %s", records[i].username, records[i].password);
		}
		fclose(loginFile);
	}
	else {
		printf("Couldn't open login database");
	}

	//get username
	printf("Enter your username: ");
	scanf("%s", username);

	//get user password
	printf("Enter your password: ");
	//mask user input for password
	for (int i = 0; i < 6; i++) {
		password[i] = getch();
		printf("*");
	}

	//check username and password against login records
	int match = 1;
	for (int i = 0; i < 3; i++) {
		if (strcmp(records[i].username, username) == 0) {
			//if username is found check every character in passwords
			for (int j = 0; j < 6; j++) {
				if (records[i].password[j] != password[j]) {
					match = 0;
					break;
				}
			}
			if (match == 1) {
				printf("\nWelcome %s!", username);
				return true;
			}
		}
	}
	printf("\nSorry, username and password were incorrect!");
	return false;
}

int displayMainMenu() {

	int choice;

	printf("\nWelcome to the Rugby Database!");

	printf("\n1 - Add a player to the database");
	printf("\n2 - Display all players in database");
	printf("\n3 - Display player details");
	printf("\n4 - Update a players statistic");
	printf("\n5 - Delete a player");
	printf("\n6 - Generate statistics");
	printf("\n7 - Quit");
	printf("\nYour choice: ");
	scanf("%d", &choice);

	return choice;
}

//function that displays all players' details from the database
void displayPlayers(node_t* head) {

	node_t* tmp = (node_t*)malloc(sizeof(node_t));
	tmp = head;

	while (tmp != NULL) {
		displayPlayer(tmp->player);

		tmp = tmp->next;
	}
}

//function that gets details of a new player from user input
player_t* addPlayer(node_t* head) {

	player_t* newPlayer = (player_t*)malloc(sizeof(player_t));
	node_t* tmp = (node_t*)malloc(sizeof(node_t));
	tmp = head;

	boolean at;
	boolean dot;
	boolean duplicate;

	//check if irfu number is unique
	do {
		duplicate = false;
		printf("Enter Players' IRFU: ");
		scanf("%d", &newPlayer->irfu);

		for (; tmp != NULL; tmp = tmp->next) {
			if (tmp->player->irfu == newPlayer->irfu) {
				duplicate = true;
				printf("\nIRFU Number already exists, try again!");
				break;
			}
		}
	} while (duplicate);

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

	//check if email has both an '@' an a dot 
	do {
		at = false;
		dot = false;

		printf("Enter Players' email: ");
		scanf("%s", newPlayer->email);

		for (int i = 0; i < strlen(newPlayer->email); i++) {
			if (newPlayer->email[i] == '@') {
				at = true;
			}
			else if (newPlayer->email[i] == '.') {
				dot = true;
			}
		}

	} while (!at || !dot);
	
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

//find user specified player and display the details
void displayDetails(node_t* head, int irfu) {

	node_t* tmp = (node_t*)malloc(sizeof(node_t));
	tmp = head;

	while (tmp != NULL) {
		if (tmp->player->irfu == irfu) {
			displayPlayer(tmp->player);
		}
		tmp = tmp->next;
	}
}

//find user specified player and update the credentials
void updatePlayer(node_t* head, int irfu) {

}

void deletePlayer(node_t* head, int irfu) {

}