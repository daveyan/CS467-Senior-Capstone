#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>

#include "Item.hpp"

using std::vector;
using std::string;

class Room {
private:
    int id;
    string name;
    vector<Item> items;
    vector<Item> itemsDropped;
    int north;
    int south;
    int east;
    int west;
    string shortDesc;
    string longDesc;
    bool visited;
public:
    Room(int id, string name, string shortDesc, string longDesc);
    void setId(int id);
    void setName(string name);
    void addNorth(int roomId);
    void addSouth(int roomId);
    void addEast(int roomId);
    void addWest(int roomId);
    void setShortDesc(string desc);
    void setLongDesc(string desc);
    void visitRoom();
    void addItem(Item item);
    int getId();
    int getNorth();
    int getSouth();
    int getEast();
    int getWest();
    string getName();
    vector<Item> getItems();
    vector<Item> getDroppedItems();
    string getDescription();
    bool isVisited();
};





#endif
