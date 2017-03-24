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

//function that searches for a player i the list by irfu number and returns the position in the list or -1 if not found
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

//function that searches for a player i the list by name and returns the position in the list or -1 if not found
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


}

//function that returns the number of elements in the list
int size(player_t* head) {
	int size = 0;
	player_t* tmp = head;

	for (; tmp != NULL; tmp = tmp->next, size++);

	return size;
}