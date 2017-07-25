#include <iostream>
#include <string.h>
#include <vector>

#include "Game.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;


void Game::addRoom(Room room) {
    rooms.push_back(room);

    // If the room being added is the first room (has id of 1), then set
    // curRoom to that room
    if (room.getId() == 1) {
        curRoom = room;
    }
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

void Game::play() {
    // Load room and item files

    char exit[] = "exit";

    cout << "Welcome Bird Spy View." << endl;
    cout << "You are an intrepid explorer trying to figure out what to do for the weekend. You aren’t too much of an outdoors person but you have been hearing stories of people being attacked by owls at a relatively close state park. Not only that, but there was a tremor at the park a few weeks ago. For most people this would dissuade them from visiting, but you feel like embracing the thrill of danger so you decide to head out." << endl;

    while (!isFinished) {
        cout << "What would you like to do?" << endl;
        memset(userInput, '\0', 256);
        cin.getline(userInput, 255);



        // Implement parser
        if (strstr(userInput, exit)) {
            isFinished = true;
        }
    }
}