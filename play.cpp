#include <iostream>

#include "ParseLine.hpp"
#include "Game.hpp"

int main() {
	Game newGame;

	//Room r(1,"Room1");		//test room
	//Room r2(2, "Room2");
	//Room r3(3, "Room3");

	//newGame.addRoom(r);		//adding test room
	//newGame.addRoom(r2);
	//newGame.addRoom(r3);

	Room roomarray[] = { Room(1, "Room1"), Room(2, "Room2"), Room(3, "Room3") };
	for (int i = 0; i < 3; i++)
		newGame.addRoom(roomarray[i]);

    newGame.play(roomarray);
    return 0;
}