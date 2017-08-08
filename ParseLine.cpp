/*****
* Filename: ParseLine.cpp
* Author: Patrick Dodd
* Description: Implementation for ParseLine.hpp
*****/

#define _CRT_SECURE_NO_WARNINGS
#include "ParseLine.hpp"
#include "Game.hpp"
#include "Item.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <cstdlib>
#include <istream>
#include <sstream>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::istream;
using std::getline;
using std::malloc;

/*****
* Function: void commandLoop(RoomAction* r_action, ObjectAction* o_action, Rooms* rooms, Objects* objects)
* Parameters: RoomAction* r_action, ObjectAction* o_action, Rooms* rooms, Objects* objects
* Description: keeps the command prompt active until the game
  ends or the user quits.
*****/
void commandLoop(RoomAction* r_action, ObjectAction* o_action, Game* newGame, Room* rooms) {
	char line[256]; // Array to hold user's entered line
	int activeGame = 0; // controls the loop
	int action;

	// Ensure the rooms use the appropriate memory address
	rooms = &newGame->rooms[0];

	Room* newroom = rooms;

	bool is_room = false, is_object = false; // flags to control search

	while (activeGame != -1) {
		memset(line, '\0', sizeof(line)); // Clear the array
		cout << "Enter line: ";
		cin.getline(line, 255); // Get input
	
		// Split line into tokens
		char* token = strtok(line, " ");
		while (token != NULL) {
			activeGame = parseLine(token, r_action, o_action, newGame, rooms);
			
			// If the user entered a room action verb, search for a room name
			if (activeGame == 1) {
				is_room = true;
				while (is_room && token != NULL) {
					newroom = isRoom(token, newGame, rooms);

					//cout << newroom.getName() <<endl;
					//cout << rooms.getName() << endl;

					if (strcmp(newroom->getName().c_str(), rooms->getName().c_str()) != 0) {
						is_room = false;
						rooms = newroom;
					}
					
					//if (action == 1)
						//is_room = false;
					else {
						token = strtok(NULL, " "); // Find the next token
						if (token == NULL && action != -1)
							cout << "You can't move in that direction..." << endl;
					}
				}
			}

			// If the user entered an object action verb, search for an object name
			if (activeGame == 2) {
				is_object = true;
				while (is_object && token != NULL) {
					action = isObject(token, newGame, rooms);
					if (action == 1)
						is_object = false;
					else {
						token = strtok(NULL, " "); // Find the next token
						if (token == NULL && action == 0)
							cout << "You didn't select an object." << endl;
					}
				}
			}

			// If user wishes to drop an item in the current room
			if (activeGame == 6) {
				is_object = true;
				while (is_object && token != NULL) {
					action = dropItem(token, newGame, rooms);
					if (action == 1)
						is_object = false;
					else {
						token = strtok(NULL, " ");
						if (token == NULL && action == 0)
							cout << "Drop failed." << endl;
					}
				}
			}
			token = strtok(NULL, " "); // Find the next token
		}
	}
}

/*****
* Function: void parseLine(char* token, RoomAction* r_action, ObjectAction* o_action, Rooms* rooms, Objects* objects)
* Parameters: char* token, RoomAction* r_action, ObjectAction* o_action, Rooms* rooms, Objects* objects
* Description: Parses the user's command and determines the action
  the game takes via the game engine
*****/
int parseLine(char* token, RoomAction* r_action, ObjectAction* o_action, Game* newGame, Room* rooms) {

	int verb = 0;
	verb = actionType(token, r_action, o_action);
	if (verb == 1) return 1; // Check for room action
	if (verb == 2) return 2; // Check for object action

	else {

		if (strcmp("Inventory", token) == 0 || strcmp("inventory", token) == 0) {

			if (newGame->getInventory().size() == 0)
				cout << "You have nothing in your inventory." << endl;
			else {
				cout << "Your Inventory\n--------------" << endl;
				for (int i = 0; i < newGame->getInventory().size(); i++) {
					cout << newGame->getInventory()[i] << endl;
				}
			}
		}


		// List keywords for user if they type the command 'help'
		if (strcmp(token, "help") == 0 || strcmp(token, "Help") == 0) {
			cout << "Insert help message here..." << endl;
			return 3;
		}

		// Save game
		if (strcmp(token, "savegame") == 0 || strcmp(token, "Savegame") == 0) {
			cout << "Savegame logic here..." << endl;
			return 4;
		}

		// Load game
		if (strcmp(token, "loadgame") == 0 || strcmp(token, "Loadgame") == 0) {
			cout << "Loadgame logic here..." << endl;
			return 5;
		}

		// Drop an item in a room
		if (strcmp("Drop", token) == 0 || strcmp("drop", token) == 0) {
			return 6;
		}

		// Quit game
		if (strcmp(token, "quit") == 0 || strcmp(token, "Quit") == 0) {
			cout << "Quit logic here..." << endl;
			return -1;
		}

	
	}
	return 0;
}

/*****
* Function: int dropItem(char* token, Game* newGame, Room* rooms)
* Parameters: char* token, Game* newGame, Room* rooms
* Description: Takes a token, pointer to a Game object, and a pointer to a Room object as 
  parameters. From the command line, if the player enters the command "Drop" or "drop",
  dropItem() is called until either a token representing an item matching an item in the
  player's inventory is passed in, or until no matches between the token and player's
  inventory are found. If a match is found, the item is fist added to the Room object's 
  vector of items, then the item is removed from the Game object's vector of items, which
  represents the player's inventory. 1 is returned, signalling a successful drop. If no
  matches are found, (i.e. the player doesn't have the item in their inventory), 0 is
  returned, signalling a failure to drop an item, and 0 is returned, prompting an error
  message to print.
*****/
int dropItem(char* token, Game* newGame, Room* rooms) {
	
	// Search inventory for item to drop
	for (int i = 0; i < newGame->getInventory().size(); i++) {
		if (strcmp(token, newGame->getInventory()[i].c_str()) == 0) {
			cout << "You dropped the " << token << " in the " << rooms->getName() << endl;

			// Add item to the new room
			rooms->addItem(newGame->getInventory()[i]);

			// Remove the item from inventory
			newGame->removeFromInv(newGame->getInventory()[i]);

			// Testing -- Print the Rooms Inventory
			cout << rooms->getName() << " inventory:" << endl;
			for (int i = 0; i < rooms->getItems().size(); i++)
				cout << rooms->getItems()[i] << endl;

			return 1;
		}
	}
	return 0;
}

/*****
* Function: int actionType(char* token, RoomAction* r_action, ObjectAction* o_action)
* Parameters: char* token, RoomAction* r_action, ObjectAction* o_action
* Description: takes a token, r_action, and o_action as parameters - compares the token
  to the contents of each action word array to determine what type of object to search for
  next in the user's input, if any at all.
*****/
int actionType(char* token, RoomAction* r_action, ObjectAction* o_action)
{
	// Check for room actions
	for (int i = 0; i < 8; i++) {
		if (strcmp(r_action->roomAction[i], token) == 0) {
			//cout << token << " is a room action verb." << endl;
			return 1;
		}
		if (strcmp(o_action->objectAction[i], token) == 0) {
			//cout << token << " is an object action verb." << endl;
			return 2;
		}
	}
	return 0;
}

/*****
* Function: int isRoom(char* token, Rooms* rooms, Objects* objects)
* Parameters: char* token, Rooms* rooms, Objects* objects
* Description: if actionType() determines the user entered a room
  action verb, this function searches for a room name. Compares token
  to the contents of the rooms and objects arrays - if token matches
  an item in rooms array, prints message stating the user has moved to
  that room and returns 1. If token matches with an item in objects array,
  user is given an error message and prompted to choose a room name and 
  returns -1.
*****/
Room* isRoom(char* token, Game* newGame, Room* rooms)
{
	int direction;

	std::system("clear");
	
	if (strcmp("North", token) == 0 || strcmp("north", token) == 0) {
		direction = rooms->getNorth();
		for (int i = 0; i < 15; i++) {
			if (newGame->rooms[i].getId() == direction) {
				cout << "You have moved to the " << newGame->rooms[i].getName().c_str() << endl;
				newGame->rooms[i].getDesc(newGame->rooms[i].isVisited(),"general");
				newGame->rooms[i].visitRoom();

				return &(newGame->rooms[i]);
			}
		}
	}

	if (strcmp("South", token) == 0 || strcmp("south", token) == 0) {
		direction = rooms->getSouth();
		for (int i = 0; i < 15; i++) {
			if (newGame->rooms[i].getId() == direction) {
				cout << "You have moved to the " << newGame->rooms[i].getName().c_str() << endl;
				newGame->rooms[i].getDesc(newGame->rooms[i].isVisited(),"general");
				newGame->rooms[i].visitRoom();

				return &(newGame->rooms[i]);
			}
		}
	}

	if (strcmp("East", token) == 0 || strcmp("east", token) == 0) {
		direction = rooms->getEast();
		for (int i = 0; i < 15; i++) {
			if (newGame->rooms[i].getId() == direction) {
				cout << "You have moved to the " << newGame->rooms[i].getName().c_str() << endl;
				newGame->rooms[i].getDesc(newGame->rooms[i].isVisited(),"general");
				newGame->rooms[i].visitRoom();

				return &(newGame->rooms[i]);
			}
		}
	}

	if (strcmp("West", token) == 0 || strcmp("west", token) == 0) {
		direction = rooms->getWest();
		for (int i = 0; i < 15; i++) {
			if (newGame->rooms[i].getId() == direction) {
				cout << "You have moved to the " << newGame->rooms[i].getName().c_str() << endl;
				newGame->rooms[i].getDesc(newGame->rooms[i].isVisited(),"general");
				newGame->rooms[i].visitRoom();

				return &(newGame->rooms[i]);
			}
		}
	}
	return rooms;
}

/*****
* Function: int isObject(char* token, Game *newGame, Rooms rooms)
* Parameters: char* token, Game* newGame, Rooms rooms
* Description: if actionType() determines the user entered an object
action verb, this function searches for an object name. Compares token
to the contents of the rooms and objects arrays - if token matches
an item in objects array, prints message stating the user has found the
object and returns 1. If token matches with an item in rooms array,
user is given an error message and prompted to choose an object name and
returns -1.
*****/
int isObject(char* token, Game* newGame, Room* rooms)
{
	for (int i = 0; i < rooms->getItems().size(); i++) {
		
		// Prevent duplicates in inventory
		for (int i = 0; i < newGame->getInventory().size(); i++) {
			if (strcmp(newGame->getInventory()[i].c_str(), token) == 0){
				cout << "You already have the " << newGame->getInventory()[i] << " in your inventory." << endl;
				
				return 1;
			}
		}

		/*
		// Special case - Metal Bar
		if (strcmp(rooms->getItems()[i].c_str(), "Metal Bar") && strcmp(token, "Metal") == 0 || strcmp(token, "metal") == 0) {
			cout << "You've grabbed the " << rooms->getItems()[i] << endl;
			cout << rooms->getItems()[i] << endl;
			newGame->addToInventory(rooms->getItems()[i]);

			return 1;
		}
		*/

		// Print Message to user saying they grabbed the item, then print the item's description
		if (strcmp(rooms->getItems()[i].c_str(), token) == 0) {
			cout << "You've grabbed the " << rooms->getItems()[i] << endl;
			cout << rooms->getItems()[i] << endl;
			newGame->addToInventory(rooms->getItems()[i]);

			// Remove the item from the room's list of items
			rooms->removeItem(token);

			return 1;
		}
	}

	// If no valid object to grab, return 0, prompting "you didn't select object" message for player
	return 0;
}
