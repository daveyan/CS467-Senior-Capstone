#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "Item.hpp"

using std::cout;
using std::endl;
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
	string roomPath;
	//string shortDesc;
	//string longDesc;
	bool visited;
public:
	Room();
	Room(int id, string name);
	void setId(int id);
	void setName(string name);
	void addNorth(int roomId);
	void addSouth(int roomId);
	void addEast(int roomId);
	void addWest(int roomId);
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
	void getDesc(bool visit,string userCommand);
	bool isVisited();
};





#endif