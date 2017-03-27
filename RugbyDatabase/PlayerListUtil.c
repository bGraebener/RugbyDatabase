//file for all functions that don't change the linked list of players

#include <string.h>
#include <stdlib.h>
#include "PlayerListUtil.h"
#include "PlayerList.h"

typedef union {

	position pos;

	float weight;

}group;

typedef struct
{
	int amount;

	group group;

	int tacklesArray[4];
	int metresArray[4];


}stats;

//
//typedef struct
//{
//	int amount;
//
//	position pos;
//
//	int tacklesArray[4];
//	int metresArray[4];
//
//
//}positionStats;
//
//
//typedef struct
//{
//	int amount;
//
//	float weight;
//
//	int tacklesArray[4];
//	int metresArray[4];
//
//
//}weightStats;


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

void displayStats(stats* group, FILE* out) {

	fprintf(out, "\nAmount of players in group: %d", group->amount);

	fprintf(out, "\n%.2f%% miss no tackles:", group->tacklesArray[0] / (float)group->amount * 100);
	fprintf(out, "\t\t\t%.2f%% make no metres", group->metresArray[0] / (float)group->amount * 100);

	fprintf(out, "\n%.2f%% miss less than 3 tackles", group->tacklesArray[1] / (float)group->amount * 100);
	fprintf(out, "\t\t\t%.2f%% make less than 10 metres", group->metresArray[1] / (float)group->amount * 100);

	fprintf(out, "\n%.2f%% miss less than 5 tackles", group->tacklesArray[2] / (float)group->amount * 100);
	fprintf(out, "\t\t\t%.2f%% make less than 20 metres", group->metresArray[2] / (float)group->amount * 100);

	fprintf(out, "\n%.2f%% miss more than 5 tackles", group->tacklesArray[3] / (float)group->amount * 100);
	fprintf(out, "\t\t\t%.2f%% make more than 20 metres", group->metresArray[3] / (float)group->amount * 100);
}

//function that generates a report of stats for all players in a group specified by the user
void generateStats(player_t* head, FILE* out) {

	//TODO
	int choice;

	do {

		printf("\nShow Statistics sorted by:");
		printf("\n1 - Player Position");
		printf("\n2 - Weight");
		printf("\nYour choice: ");
		scanf("%d", &choice);

	} while (choice != 1 && choice != 2);

	player_t* tmp = head;

	if (choice == 1) {

		generateStatsByPosition(tmp, out);
	}
	else {
		generateStatsByWeight(tmp, out);
	}


}

void generateStatsByWeight(player_t* tmp, FILE* out) {

	int numOfPlayers = size(tmp);	
	int counter = 0;
	int i;
	
	/*weightStats* statsArray = (weightStats*)malloc(sizeof(weightStats) * numOfPlayers);	*/
	stats* statsArray = (stats*)malloc(sizeof(stats) * numOfPlayers);

	//initialise the arrays in every struct
	for (int i = 0; i < numOfPlayers; i++) {
		statsArray[i].amount = 0;
		statsArray[i].group.weight = 0;

		for (int k = 0; k < 4; k++) {
			statsArray[i].metresArray[k] = 0;
			statsArray[i].tacklesArray[k] = 0;
		}
	}


	for (; tmp != NULL; tmp = tmp->next) {
		
		float weight = tmp->weight;

		//set the counter either to the end or to the weight that matches the current weight
		for (i = 0; i < counter && statsArray[i].group.weight != weight; i++) {}

		//record the metres and tackles for the weight group
		statsArray[i].amount++;
		statsArray[i].metresArray[tmp->metres]++;
		statsArray[i].tacklesArray[tmp->tackles]++;

		if (statsArray[i].group.weight != weight) {
			statsArray[i].group.weight = tmp->weight;
		}

		counter++;
	}

	fprintf(out, "\n\nStatisitics ordered by weight: ");

	for (i = 0; i < numOfPlayers; i++) {
		
		//division by zero guard
		if (statsArray[i].amount == 0) {
			continue;
		}

		//display stats by weight group
		fprintf(out, "\n\nWeight Group: %.2f kg: ", statsArray[i].group.weight);
		displayStats(&statsArray[i], out);
		
	}


	
}

void generateStatsByPosition(player_t* tmp, FILE* out) {

	char posArray[][25] = { "PROP", "HOOKER", "SECOND ROW", "BACK ROW", "HALF BACK", "CENTRE", "WINGER" };
	stats statsArray[7];

	//initialise the arrays in every struct
	for (int i = 0; i < 7; i++) {
		statsArray[i].amount = 0;

		for (int k = 0; k < 4; k++) {
			statsArray[i].metresArray[k] = 0;
			statsArray[i].tacklesArray[k] = 0;
		}
	}

	//gather data about metres and tackles for every position
	for (; tmp != NULL; tmp = tmp->next) {

		statsArray[tmp->position].amount++;
		statsArray[tmp->position].group.pos = tmp->position;
		statsArray[tmp->position].metresArray[tmp->metres]++;
		statsArray[tmp->position].tacklesArray[tmp->tackles]++;
	}

	fprintf(out, "\n\nStatisitics ordered by position: ");

	for (int i = 0; i < 7; i++) {

		//division by zero guard
		if (statsArray[i].amount == 0) {
			continue;
		}

		//display stats by position
		fprintf(out, "\n\nPosition: %s: ", posArray[statsArray[i].group.pos]);
		fprintf(out, "\nAmount of players in group: %d", statsArray[i].amount);

		fprintf(out, "\n%.2f%% miss no tackles:", statsArray[i].tacklesArray[0] / (float)statsArray[i].amount * 100);
		fprintf(out, "\t\t%.2f%% make no metres", statsArray[i].metresArray[0] / (float)statsArray[i].amount * 100);

		fprintf(out, "\n%.2f%% miss less than 3 tackles", statsArray[i].tacklesArray[1] / (float)statsArray[i].amount * 100);
		fprintf(out, "\t\t%.2f%% make less than 10 metres", statsArray[i].metresArray[1] / (float)statsArray[i].amount * 100);

		fprintf(out, "\n%.2f%% miss less than 5 tackles", statsArray[i].tacklesArray[2] / (float)statsArray[i].amount * 100);
		fprintf(out, "\t\t%.2f%% make less than 20 metres", statsArray[i].metresArray[2] / (float)statsArray[i].amount * 100);

		fprintf(out, "\n%.2f%% miss more than 5 tackles", statsArray[i].tacklesArray[3] / (float)statsArray[i].amount * 100);
		fprintf(out, "\t\t%.2f%% make more than 20 metres", statsArray[i].metresArray[3] / (float)statsArray[i].amount * 100);
	}
}



//function to make a deep copy of a player struct and return a pointer to it
player_t* copyPlayer(player_t* old) {
	player_t* newPlayer = (player_t*)malloc(sizeof(player_t));

	//copy ints
	newPlayer->irfu = old->irfu;
	newPlayer->age = old->age;
	newPlayer->weight = old->weight;
	newPlayer->height = old->height;

	//copy enums
	newPlayer->metres = old->metres;
	newPlayer->position = old->position;
	newPlayer->tackles = old->tackles;

	//copy strings
	strcpy(newPlayer->firstName, old->firstName);
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