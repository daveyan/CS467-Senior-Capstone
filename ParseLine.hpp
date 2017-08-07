/*****
* Filename: ParseLine.hpp
* Author: Patrick Dodd
* Description: Header File for ParseLine.cpp
*****/
#include "Room.hpp"
#include "Game.hpp"
#define MAX 1000

// Struct definitions
struct RoomAction {
	char roomAction[MAX][MAX];
};

struct ObjectAction {
	char objectAction[MAX][MAX];
};

struct Rooms {
	char rooms[MAX][MAX];
};

struct Objects {
	char objects[MAX][MAX];
};

// Function Prototypes
int dropItem(char* token, Game* newGame, Room* rooms);
int parseLine(char* token, RoomAction* r_action, ObjectAction* o_action, Game* newGame, Room* rooms);
void commandLoop(RoomAction* r_action, ObjectAction* o_action, Game* newGame, Room* rooms);
int actionType(char* token, RoomAction* r_action, ObjectAction* o_action);
Room* isRoom(char* token, Game* newGame, Room* rooms);
int isObject(char*token, Game* newGame, Room* rooms);
