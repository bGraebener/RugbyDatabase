//declarations of all functions that display a menu to the user
//also the function that verifies the user at the beginning of the program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Menu.h"


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

	return checkCredentials(records, username, password);
	
}

boolean checkCredentials(login* records, char* username, char password[6]) {
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

	printf("\n\nWelcome to the Rugby Database!");

	printf("\n1 - Add a player to the database");
	printf("\n2 - Display all players in database");
	printf("\n3 - Display player details");
	printf("\n4 - Update a players statistic");
	printf("\n5 - Delete a player");
	printf("\n6 - Generate statistics");
	printf("\n7 - Display report");
	printf("\n8 - List players in order");
	printf("\n9 - Quit");
	printf("\nYour choice: ");
	scanf("%d", &choice);

	return choice;
}

int displayUpdateMenu() {

	int choice;

	printf("\n\nWhat fields do you want to update?");
	printf("\n1 - IRFU");
	printf("\n2 - First Name");
	printf("\n3 - Last Name");
	printf("\n4 - Age");
	printf("\n5 - Weight");
	printf("\n6 - Height");
	printf("\n7 - Email");
	printf("\n8 - Club");
	printf("\n9 - Position");
	printf("\n10 - Tackles missed");
	printf("\n11 - Metres per game");
	printf("\n12 - Finished");
	printf("\nYour choice: ");
	scanf("%d", &choice);

	return choice;
}