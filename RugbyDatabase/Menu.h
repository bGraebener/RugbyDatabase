//header file for all functions that display a menu to the user
//defines the login struct that is used to verify the user

#pragma once
#include "Player.h"
#include "Main.h"


//login struct
typedef struct {
	char username[25];
	char password[6];
}login;


//function prototypes
boolean displayStartMenu();
int displayMainMenu();
boolean checkCredentials(login*, char*, char[6]);
int displayUpdateMenu();