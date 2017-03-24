//file for all functions that don't change the linked list of players

#include <stdlib.h>
#include "PlayerListUtil.h"


//function that displays all players' details from the database
void displayPlayers(player_t* head) {
	player_t* tmp = head;

	while (tmp != NULL) {
		displayPlayer(tmp);
		tmp = tmp->next;
	}
}

//find user specified player and display the details
void displayDetails(player_t* head) {

	//ask the user for either player name or irfu
	int playerLocation;
	playerLocation = searchForPlayer(head);

	if (playerLocation < 0) {
		printf("Player not found!");
		return;
	}

	player_t* tmp = head;

	//iterate to player in list
	for (int i = 0; i < playerLocation; i++) {
		tmp = tmp->next;
	}

	//display player information
	displayPlayer(tmp);
}

//function that searches for a player in the list by irfu number and returns the position in the list or -1 if not found
int searchByIrfu(player_t* head, int irfu) {
	player_t* tmp = head;
	int location = -1;

	for (; tmp != NULL; tmp = tmp->next) {
		location++;
		if (tmp->irfu == irfu) {
			return location;
		}
	}
	return -1;
}

//function that searches for a player in the list by name and returns the position in the list or -1 if not found
int searchByName(player_t* head, char* firstName, char* lastName) {

	player_t* tmp = head;
	int location = -1;

	for (; tmp != NULL; tmp = tmp->next) {
		location++;
		if (strcmp(tmp->lastName, lastName) == 0 && strcmp(tmp->firstName, firstName) == 0) {
			return location;
		}
	}
	return -1;
}


//function that gives the user the option to find a player either by name or by irfu
int searchForPlayer(player_t* head) {

	int choice;
	int playerLocation;
	int irfu;
	char firstName[20];
	char lastName[20];

	//give option irfu or name
	do {
		printf("\n1 - Find Player by name");
		printf("\n2 - Find Player by irfu number");
		printf("\nYour choice: ");
		scanf("%d", &choice);
	} while (choice != 1 && choice != 2);

	//call specific function according to user choice
	if (choice == 1) {
		printf("Enter Player first and last name: ");
		scanf("%s %s", firstName, lastName);
		playerLocation = searchByName(head, firstName, lastName);
	}
	else if (choice == 2) {
		printf("Enter Player irfu: ");
		scanf("%d", &irfu);
		playerLocation = searchByIrfu(head, irfu);
	}

	if (playerLocation < 0) {
		return -1;
	}

	return playerLocation;
}

//function that generates a report of stats for all players in a group specified by the user
void generateStats(player_t* head) {

	//TODO
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

//function that returns the number of elements in the list
int size(player_t* head) {
	int size = 0;
	player_t* tmp = head;

	for (; tmp != NULL; tmp = tmp->next, size++);

	return size;
}