#include <iostream>

#include "Game.hpp"

int main() {
	Game newGame;

	Room r(1,"Room1");		//test room
	Item i(1,"crowbar");

	newGame.addRoom(r);		//adding test room
	newGame.addItem(i);

    newGame.play();
    return 0;
}