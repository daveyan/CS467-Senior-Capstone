#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <unordered_map>
#include "Room.hpp"
#include "Item.hpp"

using std::vector;
using std::string;


class Game {
private:
    vector<string> items;
    char userInput[256];
    vector<string> helpInfo;
    std::unordered_map<string,string> itemInfo;
public:
    bool isFinished = false;
    vector<Room> rooms;
    Room* getCurRoom();
    int curRoom;
    void addRoom(Room room);
    void addItem(string item);
    void addToInventory(string item);
    void removeFromInv(string item);
    vector<string> inventory;
    vector<string> getInventory();
    void loadFiles();
    bool inInventory(string item);
    void play();
    void clearInv();
    void readHelpInfo();
    vector<string> getHelpInfo();
    void readItemInfo();
    std::unordered_map<string,string> getItemInfo();

};

#endif
