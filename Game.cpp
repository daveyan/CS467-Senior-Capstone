#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <algorithm>

#include "ParseLine.hpp"
#include "Game.hpp"

using std::cout;
using std::cin;
using std::endl;

int Game::getcurRoom() {
    return curRoom;
}

void Game::setcurRoom(int i){
	curRoom = i;
}

void Game::addRoom(Room room) {
    rooms.push_back(room);
}

void Game::addItem(string item) {
    items.push_back(item);
}

void Game::addToInventory(string item) {
    inventory.push_back(item);
}

void Game::removeFromInv(string item) {
    inventory.erase(std::remove(inventory.begin(), inventory.end(), item), inventory.end());
}

vector<string> Game::getInventory() {
	return inventory;
}

void Game::clearInv(){
	inventory.clear();
}

void Game::play(Game newGame, Room rooms) {
    // Load room and item files


    // Room action verbs
	char rAction[10][100] = {
		"move",
		"Move",
		"go",
		"Go",
		"walk",
		"Walk",
		"run",
		"Run"
		"travel",
		"Travel"
	};

	// Item action verbs
	char oAction[10][100] = {
		"pick",
		"Pick",
		"grab",
		"Grab",
		"use",
		"Use",
		"throw",
		"Throw",
		"take",
		"Take"
	};

	// Feature action verbs
	char fAction[10][100] = {
		"look",
		"Look",
		"peer",
		"Peer",
		"view",
		"View",
		"examine",
		"Examine",
		"inspect",
		"Inspect"
	};



	/* Initialize all structs and fill their arrays */
	RoomAction* r_action = (RoomAction*)malloc(sizeof(RoomAction));
	for (int i = 0; i < 8; i++) {
		strcpy(r_action->roomAction[i], rAction[i]);
	}

	ObjectAction* o_action = (ObjectAction*)malloc(sizeof(ObjectAction));
	for (int i = 0; i < 8; i++) {
		strcpy(o_action->objectAction[i], oAction[i]);
	}

	FeatureAction* f_action = (FeatureAction*)malloc(sizeof(FeatureAction));
	for (int i = 0; i < 10; i++) {
		strcpy(f_action->featureAction[i], fAction[i]);
	}





    char exit[] = "exit";
    //temp before parse
    char look[] = "look";

    cout << "Welcome to the Adventure of Pictor." << endl << endl;

    if (rooms.getId() == 1) {

	    //cout << rooms.getDescription() << endl;

		//cout << "[Current Room] ";
		//cout << newGame.rooms[newGame.getcurRoom()].getName() << endl;

    	newGame.setcurRoom(1); 		//entrance == 1;
	    cout << newGame.rooms[1].getLongDesc() << endl;
	    newGame.rooms[1].visitRoom();
    }
	   


    commandLoop(r_action, o_action, f_action, &newGame, &rooms);

    
}
