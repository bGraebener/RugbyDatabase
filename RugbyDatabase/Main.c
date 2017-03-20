#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "Main.h"
#include "Menu.h"
#include "Player.h"


void main() {

	int choice;
	int irfu;
	int location;

	boolean login = displayStartMenu();

	if (!login) {
		_getch();
		return;
	}
	
	//get existing records from file
	node_t* list = NULL;
	populateList(&list);

	player_t* newPlayer;

	choice = displayMainMenu();

	//
	switch (choice)
	{
	case 1:
		newPlayer = addPlayer(list);
		insertSorted(list, newPlayer);
		break;
	case 2:
		displayPlayers(list);
		break;
	case 3:
		printf("Enter Irfu Number of player to display: ");
		scanf("%d", &irfu);
		displayDetails(list, irfu);
		break;
	case 4:
		printf("Enter Irfu Number of player to update: ");
		scanf("%d", &irfu);
		updatePlayer(list, irfu);
		break;
	case 5:
		printf("Enter Irfu Number of player to delete: ");
		scanf("%d", &irfu);
		deletePlayer(list, irfu);
		break;
	case 6:
		break;
	case 7:
		printf("Goodbye!");
		break;
	default:
		break;
	}

	
	//print database to file
	printToFile(list);

	//free dynamically allocated memory
	free(list);

	_getch();
}


//function that populates the list at the beginning of the program from the file "Rugby.txt"
void populateList(node_t** head) {

	//attempt to open the file with the previosly saved records
	FILE* in = fopen("Rugby.txt", "r");
	int result;
	player_t* newPlayer;

	//check if file is open
	if (in != NULL) {

		//temporary head node copy
		node_t* tmp = (node_t*)malloc(sizeof(node_t));
		tmp = *head;

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
void addFirst(node_t** head, player_t* newPlayer) {

	//temporary head node copy
	node_t* tmp = (node_t*)malloc(sizeof(node_t));
	tmp = *head;

	//the node that holds the new player
	node_t* newNode;
	newNode = (node_t*)malloc(sizeof(node_t));
	newNode->player = newPlayer;
	newNode->next = NULL;

	//make the old head the new nodes' next
	//make the new node the new head node
	newNode->next = *head;
	*head = newNode;

}

//function that adds new players to the list and inserts 
//them at the appropriate place by order of the irfu number
void insertSorted(node_t** head, player_t* newPlayer) {

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
	node_t* tmp = (node_t*)malloc(sizeof(node_t));
	node_t* previous = (node_t*)malloc(sizeof(node_t));
	tmp = *head;

	//node that holds the new player 
	node_t* newNode;
	newNode = (node_t*)malloc(sizeof(node_t));
	newNode->player = newPlayer;
	newNode->next = NULL;

	//find the two nodes that the new node gets inserted between
	for (int i = 0; i < position; i++) {
		previous = tmp;
		tmp = tmp->next;
	}

	//insert new node
	previous->next = newNode;
	newNode->next = tmp;
}

//function to find a new players position inside the linked list by order of irfu number
int findLocation(node_t* head, int irfu) {

	//temporary head node copy
	node_t* tmp = (node_t*)malloc(sizeof(node_t));
	tmp = head;
	int position = 0;

	//determine correct position by checking irfu number against existing records
	while (tmp->player->irfu < irfu) {
		position++;
		tmp = tmp->next;

		if (tmp == NULL) {
			break;
		}
	}
	return position;
}

//function to write the players database to file
void printToFile(node_t* head) {

	//temporary head node copy
	node_t* tmp = (node_t*)malloc(sizeof(node_t));
	tmp = head;

	//attempt to open database file
	FILE* out = fopen("Rugby.txt", "w");

	//if file is open write every record in the list to the file
	if (out != NULL) {
		while (tmp != NULL) {
			fprintf(out, "%d ", tmp->player->irfu);
			fprintf(out, "%s ", tmp->player->firstName);
			fprintf(out, "%s ", tmp->player->lastName);
			fprintf(out, "%d ", tmp->player->age);
			fprintf(out, "%f ", tmp->player->height);
			fprintf(out, "%f ", tmp->player->weight);
			fprintf(out, "%s ", tmp->player->club);
			fprintf(out, "%s ", tmp->player->email);
			fprintf(out, "%d ", tmp->player->position + 1);
			fprintf(out, "%d ", tmp->player->tackles + 1);
			fprintf(out, "%d ", tmp->player->metres + 1);
			fprintf(out, "\n");
			tmp = tmp->next;
		}
		//close the file
		fclose(out);
	}
	else {
		//file couldn't be opened
		printf("Couldn't write to file");
		return;
	}
}