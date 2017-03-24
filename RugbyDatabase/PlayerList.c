#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "PlayerList.h"

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

//find user specified player and update the information
void updatePlayer(player_t* head) {
	
	int choice;
	int playerLocation;
	int pos, tackles, metres;
	
	playerLocation = searchForPlayer(head);

	if (playerLocation < 0) {
		printf("Player not found!");
		return;
	}

	player_t* tmp = head;

	for (int i = 0; i < playerLocation; i++) {
		tmp = tmp->next;
	}

	//display player information
	displayPlayer(tmp);

	do {		
		choice = displayUpdateMenu();

		switch (choice)
		{
		case 1:
			printf("Enter new IRFU: ");
			scanf("%d", &tmp->irfu);
			break;
		case 2:
			printf("Enter new First Name: ");
			scanf("%s", tmp->firstName);
			break;
		case 3:
			printf("Enter new Last Name: ");
			scanf("%s", tmp->lastName);
			break;
		case 4:
			printf("Enter new Age: ");
			scanf("%d", &tmp->age);
			break;
		case 5:
			printf("Enter new Weight: ");
			scanf("%d", &tmp->weight);
			break;
		case 6:
			printf("Enter new Height: ");
			scanf("%d", &tmp->height);
			break;
		case 7:
			printf("Enter new Email: ");
			scanf("%s", tmp->email);
			break;
		case 8:
			printf("Enter new Club: ");
			scanf("%s", tmp->club);
			break;
		case 9:
			pos = getPlayerPosition();
			tmp->position = pos - 1;
			break;
		case 10:
			tackles = getPlayerTackles();
			tmp->tackles = tackles - 1;
			break;
		case 11:
			metres = getPlayerMetres();
			tmp->metres = metres - 1;
			break;
		
		default:
			break;
		}




	} while (choice != -1);



	//TODO
}

//function that gives the user the option to find a player either by name or by irfu
int searchForPlayer(player_t* head) {

	int choice;
	int playerLocation;
	int irfu;
	char firstName[20];
	char lastName[20];

	do {
		printf("\n1 - Find Player by name");
		printf("\n2 - Find Player by irfu number");
		printf("\nYour choice: ");
		scanf("%d", &choice);
	} while (choice != 1 && choice != 2);

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

void deletePlayer(player_t** head, int irfu) {

	//create two temporary 'cursor' pointers to keep track of 
	//the current node and the one before since in a singly linked list 
	//there is no way of going backwards
	player_t* tmp;
	player_t* prior;

	tmp = head;

	//find location of player in list
	int position = searchByIrfu(*head, irfu);

	if (position < 0) {
		printf("Couldn't find player!");

	}
	else if (position == 0) {
		deleteFirst(head);
	}
	else {
		for (int i = 0; i < position; i++) {
			prior = tmp;
			tmp = tmp->next;
		}

		prior->next = tmp->next;
		free(tmp);
		printf("\nDeleted Player..");
	}
}

//function to delete the first element in the list
void deleteFirst(player_t** head) {
	player_t* tmp = *head;

	*head = tmp->next;
	free(tmp);
}

void generateStats(player_t* head) {


}



//function that populates the list at the beginning of the program from the file "Rugby.txt"
void populateList(player_t** head) {

	//attempt to open the file with the previosly saved records
	FILE* in = fopen("Rugby.txt", "r");
	int result;
	player_t* newPlayer;

	//check if file is open
	if (in != NULL) {

		//temporary head node copy
		player_t* tmp = *head;

		//read in all records from the file in to the linked list
		while (!feof(in)) {

			newPlayer = (player_t*)malloc(sizeof(player_t));

			fscanf(in, "%d", &newPlayer->irfu);
			fscanf(in, "%s", newPlayer->firstName);
			fscanf(in, "%s", newPlayer->lastName);
			fscanf(in, "%d", &newPlayer->age);
			fscanf(in, "%f", &newPlayer->height);
			fscanf(in, "%f", &newPlayer->weight);
			fscanf(in, "%s", newPlayer->club);
			fscanf(in, "%s", newPlayer->email);

			int pos;
			fscanf(in, "%d", &pos);
			newPlayer->position = pos - 1;

			int tackles;
			fscanf(in, "%d", &tackles);
			newPlayer->tackles = tackles - 1;

			int metres;
			result = fscanf(in, "%d", &metres);
			newPlayer->metres = metres - 1;

			//check if end of file is reached
			if (result < 0) {
				break;
			}

			//if the list is empty store the new record in the beginning of the list
			if (*head == NULL) {
				addFirst(head, newPlayer);
			}
			//else insert the record at the appropriate position
			else {
				insertSorted(head, newPlayer);
			}
		}
		//close the file
		fclose(in);
	}
	//file couldn't be opened
	else {
		printf("Couldn't read file");
		return;
	}
}

//function that adds a new player at the beginning of the list
void addFirst(player_t** head, player_t* newPlayer) {

	//make the old head the new nodes' next
	//make the new node the new head node
	newPlayer->next = *head;
	*head = newPlayer;
}

//function that adds new players to the list and inserts 
//them at the appropriate place by order of the irfu number
void insertSorted(player_t** head, player_t* newPlayer) {

	//if list is empty add new player to the beginning
	if (*head == NULL) {
		addFirst(head, newPlayer);
		return;
	}

	//find the right position by order of irfu number
	int position = findLocation(*head, newPlayer->irfu);

	//if irfu number is first in list add to the beginning
	if (position == 0) {
		addFirst(head, newPlayer);
		return;
	}

	//two cursor nodes to be able to insert between two nodes
	player_t* tmp;
	player_t* previous;
	tmp = *head;

	//find the two nodes that the new node gets inserted between
	for (int i = 0; i < position; i++) {
		previous = tmp;
		tmp = tmp->next;
	}

	//insert new node
	previous->next = newPlayer;
	newPlayer->next = tmp;
}

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

int size(player_t* head) {
	int size = 0;

	player_t* tmp = head;

	for (; tmp != NULL; tmp = tmp->next, size++);

	return size;

}