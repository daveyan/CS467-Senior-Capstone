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
    vector<string> items;
    vector<string> itemsDropped;
    int north;
    int south;
    int east;
    int west;
    string northExitStatus = "";
    string southExitStatus = "";
    string eastExitStatus = "";
    string westExitStatus = "";
    string shortDesc;
    string longDesc;
    string feature1Response;
    string feature2Response;
    string roomPath;
    string feature1Key;
    string feature2Key;
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
	void setNorthExitStatus(string status);
    void setSouthExitStatus(string status);
    void setEastExitStatus(string status);
    void setWestExitStatus(string status);
    void setShortDesc(string desc);
    void setLongDesc(string desc);
    string getShortDesc();
    string getLongDesc();
    void visitRoom();
	void addItem(string item);
	int getId();
	int getNorth();
	int getSouth();
	int getEast();
	int getWest();
	string getNorthExitStatus();
    string getSouthExitStatus();
    string getEastExitStatus();
    string getWestExitStatus();
	string getName();
	vector<string> getItems();
    vector<string> getDroppedItems();
	string getDesc(string userCommand);
	string getDescription();
    string getFeature1Response();
    string getFeature2Response();
    void setFeature1Response(string resp);
    void setFeature2Response(string resp);
    void setFeature1Key(string key);
    void setFeature2Key(string key);
    string getFeature1Key();
    string getFeature2Key();
	bool isVisited();
    void setVisited(bool v);

    void clearRoomInv();
    void removeItem(string item);
};





#endif