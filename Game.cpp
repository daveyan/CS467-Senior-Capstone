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

void Game::addItem(Item item) {
    items.push_back(item);
}

void Game::addToInventory(int item) {
    inventory.push_back(item);
}

void Game::removeFromInv(int item) {
    inventory.erase(std::remove(inventory.begin(), inventory.end(), item), inventory.end());
}

vector<int> Game::getInventory() {
	return inventory;
}

void Game::play(Game newGame, Room rooms) {
    // Load room and item files


    /* For testing -- not to be used in final version */
	char rAction[10][100] = {
		"move",
		"Move",
		"go",
		"Go",
		"walk",
		"Walk",
		"run",
		"Run"
	};

	/* For testing -- not to be used in final version */
	char oAction[8][100] = {
		"pick",
		"Pick",
		"grab",
		"Grab",
		"use",
		"Use",
		"look",
		"Look"
	};

	/* For testing -- not to be used in final version */
	char rms[3][100] = {
		"cave",
		"vault",
		"cellar"
	};

	/* For testing -- not to be used in final version */
	char objs[3][100] = {
		"knife",
		"shovel",
		"hammer"
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

	Rooms* roomnames = (Rooms*)malloc(sizeof(Rooms));
	for (int i = 0; i < 3; i++) {
		strcpy(roomnames->rooms[i], rms[i]);
	}

	Objects* objects = (Objects*)malloc(sizeof(Objects));
	for (int i = 0; i < 3; i++) {
		strcpy(objects->objects[i], objs[i]);
	}




    char exit[] = "exit";
    //temp before parse
    char look[] = "look";

    cout << "Welcome to the Adventure of Pictor." << endl << endl;

    newGame.setcurRoom(0);

    newGame.rooms[0].getDesc(newGame.rooms[0].isVisited(),"general");
	newGame.rooms[0].visitRoom();
	   


    commandLoop(r_action, o_action, &newGame, rooms);

    
}
