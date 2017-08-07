/*****
* Filename: ParseLine.cpp
* Author: Patrick Dodd
* Description: Implementation for ParseLine.hpp
*****/

#define _CRT_SECURE_NO_WARNINGS
#include "ParseLine.hpp"
#include "Game.hpp"
#include "Room.hpp"
#include "Item.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <cstdlib>
#include <istream>
#include <sstream>
#include <algorithm>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::istream;
using std::getline;
using std::malloc;
using std::ifstream;
using std::ofstream;

using std::swap;

/*****
* Function: void commandLoop(RoomAction* r_action, ObjectAction* o_action, Rooms* rooms, Objects* objects)
* Parameters: RoomAction* r_action, ObjectAction* o_action, Rooms* rooms, Objects* objects
* Description: keeps the command prompt active until the game
  ends or the user quits.
*****/
void commandLoop(RoomAction* r_action, ObjectAction* o_action, Game* newGame, Room rooms) {
	char line[256]; // Array to hold user's entered line
	int activeGame = 0; // controls the loop
	int action;
	Room newroom = rooms;

	bool is_room = false, is_object = false; // flags to control search

	
	while (activeGame != -1) {

		cout << "[Current Room] ";
		cout << newGame->rooms[newGame->getcurRoom()].getName() << endl;

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
					newGame->setcurRoom(newroom.getId());

					//cout << newroom.getName() <<endl;
					//cout << rooms.getName() << endl;

					if (strcmp(newroom.getName().c_str(), rooms.getName().c_str()) != 0) {
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

			if (activeGame == 5) {
				std::system("clear");
				cout << ">>> Game Loaded <<<" << endl;
				
				newGame->rooms[newGame->getcurRoom()].getDesc(newGame->rooms[newGame->getcurRoom()].isVisited(),"general");
				newGame->rooms[newGame->getcurRoom()].visitRoom();


				is_room = true;
				while (is_room && token != NULL) {
					newroom = newGame->rooms[newGame->getcurRoom()];
					newGame->setcurRoom(newroom.getId());

					//cout << newroom.getName() <<endl;
					//cout << rooms.getName() << endl;

					if (strcmp(newroom.getName().c_str(), rooms.getName().c_str()) != 0) {
						is_room = false;
						rooms = newroom;
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
int parseLine(char* token, RoomAction* r_action, ObjectAction* o_action, Game* newGame, Room rooms) {

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
			ofstream savefile;
			savefile.open ("savegame.txt");
			//write players position
			savefile << newGame->getcurRoom() << endl;
			//savefile <<"\n";
			//write number of items in inventory
			savefile << newGame->getInventory().size() << endl;
			for (int i = 0; i < newGame->getInventory().size();i++){
				savefile << newGame->getInventory()[i] << endl;
			}


			//GETTING THE ITEMS IN THE ROOM - NOT NECESSARY? 
			/*
			for(int i = 0; i < newGame->rooms.size();i++){
				savefile << newGame->rooms[i].getName() + "\n";

				for(int j = 0; j < newGame->rooms[i].getItems().size(); j++){
					savefile << newGame->rooms[i].getItems()[j].getName() + "\n";
				}
				
			}
			*/
			savefile.close();


			return 4;
		}

		// Load game
		if (strcmp(token, "loadgame") == 0 || strcmp(token, "Loadgame") == 0) {
			cout << "Loadgame logic here..." << endl;
			ifstream loadfile;
			loadfile.open ("savegame.txt");
			vector<string> loadfileData;
			string s;
			int data;
			while(std::getline(loadfile,s)){
				loadfileData.push_back(s);
			}

			int loadRoomId = std::stoi(loadfileData[0]); 			//line one is current position
			newGame->setcurRoom(loadRoomId);

			int numItems = std::stoi(loadfileData[1]);				//line two has number of items in inventory

			newGame->getInventory().clear; 							//clear all items from inventory

			
			for (int i = 0; i < numItems; i++){
				newGame->addToInventory(rooms.getItems()[i].getName());
			}


			
			
			return 5;
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
Room isRoom(char* token, Game* newGame, Room rooms)
{
	int direction;

	std::system("clear");
	
	if (strcmp("North", token) == 0 || strcmp("north", token) == 0) {
		direction = rooms.getNorth();
		for (int i = 0; i < 15; i++) {
			if (newGame->rooms[i].getId() == direction) {
				cout << "You have moved to the " << newGame->rooms[i].getName().c_str() << endl;
				newGame->rooms[i].getDesc(newGame->rooms[i].isVisited(),"general");
				newGame->rooms[i].visitRoom();

				

				return newGame->rooms[i];
			}
		}
	}

	if (strcmp("South", token) == 0 || strcmp("south", token) == 0) {
		direction = rooms.getSouth();
		for (int i = 0; i < 15; i++) {
			if (newGame->rooms[i].getId() == direction) {
				cout << "You have moved to the " << newGame->rooms[i].getName().c_str() << endl;
				newGame->rooms[i].getDesc(newGame->rooms[i].isVisited(),"general");
				newGame->rooms[i].visitRoom();

				

				return newGame->rooms[i];
			}
		}
	}

	if (strcmp("East", token) == 0 || strcmp("east", token) == 0) {
		direction = rooms.getEast();
		for (int i = 0; i < 15; i++) {
			if (newGame->rooms[i].getId() == direction) {
				cout << "You have moved to the " << newGame->rooms[i].getName().c_str() << endl;
				newGame->rooms[i].getDesc(newGame->rooms[i].isVisited(),"general");
				newGame->rooms[i].visitRoom();

				
				return newGame->rooms[i];
			}
		}
	}

	if (strcmp("West", token) == 0 || strcmp("west", token) == 0) {
		direction = rooms.getWest();
		for (int i = 0; i < 15; i++) {
			if (newGame->rooms[i].getId() == direction) {
				cout << "You have moved to the " << newGame->rooms[i].getName().c_str() << endl;
				newGame->rooms[i].getDesc(newGame->rooms[i].isVisited(),"general");
				newGame->rooms[i].visitRoom();

			
				return newGame->rooms[i];
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
int isObject(char* token, Game* newGame, Room rooms)
{
	for (int i = 0; i < rooms.getItems().size(); i++) {
		
		// Prevent duplicates in inventory
		for (int i = 0; i < newGame->getInventory().size(); i++) {
			if (strcmp(newGame->getInventory()[i].c_str(), token) == 0){
				cout << "You already have the " << newGame->getInventory()[i] << " in your inventory." << endl;
				
				return 1;
			}
		}

		// Special case - Metal Bar
		if (strcmp(rooms.getItems()[i].getName().c_str(), "Metal Bar") && strcmp(token, "Metal") == 0 || strcmp(token, "metal") == 0) {
			cout << "You've grabbed the " << rooms.getItems()[i].getName() << endl;
			cout << rooms.getItems()[i].getDescription() << endl;
			newGame->addToInventory(rooms.getItems()[i].getName());

			return 1;
		}

		// Print Message to user saying they grabbed the item, then print the item's description
		if (strcmp(rooms.getItems()[i].getName().c_str(), token) == 0) {
			cout << "You've grabbed the " << rooms.getItems()[i].getName() << endl;
			cout << rooms.getItems()[i].getDescription() << endl;
			newGame->addToInventory(rooms.getItems()[i].getName());
			

			return 1;
		}
	}

	// If no valid object to grab, return 0, prompting "you didn't select object" message for player
	return 0;
}
