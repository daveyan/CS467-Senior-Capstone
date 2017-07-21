#include <iostream>

#include "Game.hpp"

int main() {
	Game newGame;

	Room r(1,"Room1");		//test room

	newGame.addRoom(r);		//adding test room

    newGame.play();
    return 0;
}