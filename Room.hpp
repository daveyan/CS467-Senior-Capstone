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
	void setNorthExitStatus(int status);
    void setSouthExitStatus(int status);
    void setEastExitStatus(int status);
    void setWestExitStatus(int status);
    void setShortDesc(string desc);
    void setLongDesc(string desc);
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
    void removeItem(string item);
	vector<string> getItems();
    vector<string> getDroppedItems();
	void getDesc(bool visit,string userCommand);
	string getDescription();
    string getFeature1Response();
    string getFeature2Response();
	bool isVisited();
};





#endif