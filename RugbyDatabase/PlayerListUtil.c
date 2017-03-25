//file for all functions that don't change the linked list of players

#include <string.h>
#include <stdlib.h>
#include "PlayerListUtil.h"
#include "PlayerList.h"



//function that sends all players' details to the specified output stream
void displayPlayers(player_t* head, FILE* out) {
	player_t* tmp = head;

	while (tmp != NULL) {
		displayPlayer(tmp, out);
		tmp = tmp->next;
	}
}

//find user specified player and display the details
int displayDetails(player_t* head) {
		
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
		printf("Player not found!");
		return -1;
	}

	player_t* tmp = head;

	//iterate to player in list
	for (int i = 0; i < playerLocation; i++) {
		tmp = tmp->next;
	}

	//display player information
	displayPlayer(tmp, stdout);

	return playerLocation;
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


//function that generates a report of stats for all players in a group specified by the user
void generateStats(player_t* head) {

	//TODO
}

//function to make a deep copy of a player struct and return a pointer to it
player_t* copyPlayer(player_t* old) {
	player_t* newPlayer = (player_t*)malloc(sizeof(player_t));

	//copy ints
	newPlayer->irfu = old->irfu;
	newPlayer->age = old->age;
	newPlayer->weight= old->weight;
	newPlayer->height= old->height;

	//copy enums
	newPlayer->metres = old->metres;
	newPlayer->position = old->position;
	newPlayer->tackles = old->tackles;

	//copy strings
	strcpy(newPlayer->firstName , old->firstName);
	strcpy(newPlayer->lastName, old->lastName);
	strcpy(newPlayer->email, old->email);
	strcpy(newPlayer->club, old->club);

	newPlayer->next = NULL;

	return newPlayer;
}

//function that displays players of two positions in order of their height
void displayInOrder(player_t* head) {
	
	player_t* tmp = head;

	//make a new list in order of height consisting only of second_row and back_row players
	player_t* newList = NULL;
	
	player_t* newListPrev;

	//find all players in the list that match the position criteria
	while (tmp != NULL) {
		if (tmp->position == SECOND_ROW || tmp->position == BACK_ROW) {

			//copy the player node 
			player_t* newPlayer = copyPlayer(tmp);

			//if the list is empty, insert the node at the beginning
			if (newList == NULL) {
				addFirst(&newList, newPlayer);
				tmp = tmp->next;
				continue;
			}

			//find the right position by order of height
			int position = findLocation(newList, tmp->height, HEIGHT);

			//if position is first in list add to the beginning
			if (position == 0) {
				addFirst(&newList, newPlayer);
				tmp = tmp->next;
				continue;
			}

			player_t* newListTmp = newList;

			//set the cursor nodes to the right position
			for (int i = 0; i < position; i++) {
				newListPrev = newListTmp;
				newListTmp = newListTmp->next;
			}

			//insert new node between the two cursor nodes
			newListPrev->next = newPlayer;
			newPlayer->next = newListTmp;
		}

		//progress the main list
		tmp = tmp->next;
	}

	//display the sorted list
	displayPlayers(newList, stdout);

	//free the sorted list
	freeLinkedList(newList);
}


//function to find a new players position inside the linked list by order of a specified field, either irfu or height
int findLocation(player_t* head, int num, sortField sortField) {

	//temporary head node copy
	player_t* tmp = head;
	int position = 0;


	switch (sortField)
	{
		//determine correct position by checking irfu number against existing records
	case IRFU:
		while (tmp->irfu < num) {
			position++;
			tmp = tmp->next;

			if (tmp == NULL) {
				break;
			}
		}
		break;

		//determine correct position by height 
	case HEIGHT:
		while (tmp->height < num) {
			position++;
			tmp = tmp->next;

			if (tmp == NULL) {
				break;
			}
		}
		break;

	default:
		break;
	}

	return position;
}


//function that returns the number of elements in the list
int size(player_t* head) {
	int size = 0;
	player_t* tmp = head;

	for (; tmp != NULL; tmp = tmp->next, size++);

	return size;
}