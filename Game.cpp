#include <iostream>
#include <string.h>
#include <algorithm>


#include "Game.hpp"

using std::cout;
using std::cin;
using std::endl;

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

void Game::play() {
    // Load room and item files

    char exit[] = "exit";
    //temp before parse
    char look[] = "look";

    cout << "Welcome to the Adventure of Pictor." << endl;

    while (!isFinished) {
        cout << "What would you like to do?" << endl;
        memset(userInput, '\0', 256);
        cin.getline(userInput, 255);

        //temporary "look" without parser
        if(strstr(userInput,look)){
        	items[0].getDescription(items[0].getInInventory(),"look");
        }


        // Implement parser
        if (strstr(userInput, exit)) {
            isFinished = true;
        }
    }
}