//declarations of all functions that display a menu to the user
//also the function that verifies the user at the beginning of the program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "Menu.h"

// non-global function prototype
boolean checkCredentials(login*, char*, char[6]);

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

//function that checks the user entered name and password against the records in the login array and returns whether they match or not
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

//function that prompts the user with the main menu options and returns the users choice
int displayMainMenu() {

	int choice;

	printf("\n\nWelcome to the Rugby Database!");

	printf("\n1 - Add a player to the database");
	printf("\n2 - Display all players in database");
	printf("\n3 - Display player details");
	printf("\n4 - Update a players statistic");
	printf("\n5 - Delete a player");
	printf("\n6 - Generate statistics");
	printf("\n7 - Print report to file");
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


