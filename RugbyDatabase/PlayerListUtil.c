//file for all functions that don't change the linked list of players

#include <string.h>
#include <stdlib.h>
#include "PlayerListUtil.h"
#include "PlayerList.h"


//function that sends all players' details to the specified output stream
void displayPlayers(player_t* head, FILE* out) {
	
	//check if list is empty
	if (head == NULL) {
		fprintf(out, "\nList is empty!");
		return;
	}
	
	player_t* tmp = head;

	//iterate the list until last element and call the display function for single player
	while (tmp != NULL) {
		displayPlayer(tmp, out);
		tmp = tmp->next;
	}
}

//find user specified player, display the details and return the location in the linked list
int displayDetails(player_t* head) {

	//if list is empty return invalid position
	if (head == NULL) {
		printf("\nList is empty!");
		return -1;
	}

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

//function to display a single group statistics report
void displayStats(stats* group, FILE* out) {

	fprintf(out, "\n%6.2f%% miss no tackles per game:", group->tacklesArray[0] / (float)group->amount * 100);
	fprintf(out, "\t\t%6.2f%% make no metres", group->metresArray[0] / (float)group->amount * 100);

	fprintf(out, "\n%6.2f%% miss less than 3 tackles", group->tacklesArray[1] / (float)group->amount * 100);
	fprintf(out, "\t\t%6.2f%% make less than 10 metres", group->metresArray[1] / (float)group->amount * 100);

	fprintf(out, "\n%6.2f%% miss less than 5 tackles", group->tacklesArray[2] / (float)group->amount * 100);
	fprintf(out, "\t\t%6.2f%% make less than 20 metres", group->metresArray[2] / (float)group->amount * 100);

	fprintf(out, "\n%6.2f%% miss more than 5 tackles", group->tacklesArray[3] / (float)group->amount * 100);
	fprintf(out, "\t\t%6.2f%% make more than 20 metres", group->metresArray[3] / (float)group->amount * 100);
}

//function to ask the user by which order the statistics report is to be ordered
//delegates then to the appropriate function
void generateStats(player_t* head, FILE* out) {

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

//function that generates a report of stats for all players grouped by weight
void generateStatsByWeight(player_t* tmp, FILE* out) {

	float lowerBound;

	//ask for minimum weight
	printf("What's the lower weight boundary? ");
	scanf("%f", &lowerBound);

	stats stats;
	stats.amount = 0;
	
	for (int k = 0; k < 4; k++) {
		stats.metresArray[k] = 0;
		stats.tacklesArray[k] = 0;
	}

	//iterate the whole linked list
	for (; tmp != NULL; tmp = tmp->next) {

		if (tmp->weight >= lowerBound) {
			//record the metres and tackles for the weight group
			stats.amount++;
			stats.metresArray[tmp->metres]++;
			stats.tacklesArray[tmp->tackles]++;
		}		
	}

	//guard against a division by zero
	if (stats.amount != 0) {

		fprintf(out, "\n\nWeight Group: > %.2f kg: ", lowerBound);
		fprintf(out, "\nAmount of players in group: %d", stats.amount);
		displayStats(&stats, out);
	}
	else {
		printf("\nNo player with this weight found!");
	}

}

//function that generates a report of stats for all players grouped by position
void generateStatsByPosition(player_t* tmp, FILE* out) {
	char posArray[][25] = { "Prop", "Hooker", "Second Row", "Back Row", "Half Back", "Centre", "Winger" };
	int position;

	//ask for position
	printf("\nFor which position do you want to generate statistics? ");
	position = getPlayerPosition() - 1;

	//initialise stats struct to keep track of statistics
	stats stats;	
	stats.amount = 0;

	for (int k = 0; k < 4; k++) {
		stats.metresArray[k] = 0;
		stats.tacklesArray[k] = 0;
	}

	//iterate over the list and gather data of user specified position players
	for (; tmp != NULL; tmp = tmp->next) {

		if (tmp->position == position)
		{
			stats.amount++;			
			stats.metresArray[tmp->metres]++;
			stats.tacklesArray[tmp->tackles]++;
		}
	}

	//guard against a division by zero
	if (stats.amount != 0) {

		//send the statistics to the specified output stream
		fprintf(out, "\n\nPosition: %s ", posArray[position]);
		fprintf(out, "\nAmount of players in group: %d", stats.amount);

		displayStats(&stats, out);
	}
	else {
		printf("\nNo players in this position found!");
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
	player_t* secondRowList = NULL;
	player_t* backRowList = NULL;

	player_t* newListPrev;

	//find all players in the list that match the position criteria
	while (tmp != NULL) {
		if (tmp->position == SECOND_ROW) {

			//copy the player node 
			player_t* newPlayer = copyPlayer(tmp);

			//if the list is empty, insert the node at the beginning
			if (secondRowList == NULL) {
				addFirst(&secondRowList, newPlayer);
				tmp = tmp->next;
				continue;
			}

			//find the right position by order of height
			int position = findLocation(secondRowList, tmp->height, HEIGHT);

			//if position is first in list add to the beginning
			if (position == 0) {
				addFirst(&secondRowList, newPlayer);
				tmp = tmp->next;
				continue;
			}

			player_t* newListTmp = secondRowList;

			//set the cursor nodes to the right position
			for (int i = 0; i < position; i++) {
				newListPrev = newListTmp;
				newListTmp = newListTmp->next;
			}

			//insert new node between the two cursor nodes
			newListPrev->next = newPlayer;
			newPlayer->next = newListTmp;
		}
		else if (tmp->position == BACK_ROW) {
			//copy the player node 
			player_t* newPlayer = copyPlayer(tmp);

			//if the list is empty, insert the node at the beginning
			if (backRowList == NULL) {
				addFirst(&backRowList, newPlayer);
				tmp = tmp->next;
				continue;
			}

			//find the right position by order of height
			int position = findLocation(backRowList, tmp->height, HEIGHT);

			//if position is first in list add to the beginning
			if (position == 0) {
				addFirst(&backRowList, newPlayer);
				tmp = tmp->next;
				continue;
			}

			player_t* newListTmp = backRowList;

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

	//display the sorted lists
	printf("\nSecond Row players in order of height:");
	displayPlayers(secondRowList, stdout);
	printf("\n\nBack Row players in order of height:");
	displayPlayers(backRowList, stdout);

	//free the sorted list
	freeLinkedList(secondRowList);
	freeLinkedList(backRowList);
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
