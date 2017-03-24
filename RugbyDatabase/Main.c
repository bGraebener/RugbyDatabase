#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "Main.h"
#include "Menu.h"
#include "Player.h"
#include "PlayerList.h"

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
	player_t* list = NULL;
	populateList(&list);

	player_t* newPlayer;

	
	choice = displayMainMenu();

	while (choice != 7) {
		//
		switch (choice)
		{
		case 1:
			newPlayer = createPlayer(list);
			insertSorted(&list, newPlayer);
			break;
		case 2:
			displayPlayers(list);
			break;
		case 3:			
			displayDetails(list);
			break;
		case 4:			
			updatePlayer(list);
			break;
		case 5:
			printf("Enter Irfu Number of player to delete: ");
			scanf("%d", &irfu);
			deletePlayer(&list, irfu);
			break;
		case 6:
			break;
		case 7:			
			break;
		default:
			break;
		}
		choice = displayMainMenu();
	};

	//print database to file
	printToFile(list);

	//free dynamically allocated memory
	free(list);

	printf("Goodbye!");

	_getch();
}



//function to write the players database to file
void printToFile(player_t* head) {

	//temporary head node copy
	player_t* tmp = (player_t*)malloc(sizeof(player_t));
	tmp = head;

	//attempt to open database file
	FILE* out = fopen("Rugby.txt", "w");

	//if file is open write every record in the list to the file
	if (out != NULL) {
		while (tmp != NULL) {
			fprintf(out, "%d ", tmp->irfu);
			fprintf(out, "%s ", tmp->firstName);
			fprintf(out, "%s ", tmp->lastName);
			fprintf(out, "%d ", tmp->age);
			fprintf(out, "%f ", tmp->height);
			fprintf(out, "%f ", tmp->weight);
			fprintf(out, "%s ", tmp->club);
			fprintf(out, "%s ", tmp->email);
			fprintf(out, "%d ", tmp->position + 1);
			fprintf(out, "%d ", tmp->tackles + 1);
			fprintf(out, "%d ", tmp->metres + 1);
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