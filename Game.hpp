#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "Room.hpp"
#include "Item.hpp"

using std::vector;
using std::string;

class Game {
private:
    int curRoom;
    //vector<Room> rooms;
    vector<Item> items;
    vector<string> inventory;
    char userInput[256];
    bool isFinished = false;
public:
    int getcurRoom();
    void setcurRoom(int i);
    vector<Room> rooms;
    vector<Item> allitems; //for loadgame purposes
    void addRoom(Room room);
    void addItem(Item item);
    void addToInventory(string item);
    void removeFromInv(string item);
    vector<string> getInventory();
    void clearInv();
    void play(Game newGame, Room rooms);
};

#endif
