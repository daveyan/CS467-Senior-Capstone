#pragma once
#include "feature.hpp"
#include "object.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Room
{
public:
	bool visited;
	string roomName;
	string roomDesc;
	vector<Room> roomList;
	vector<Feature> featureList;
	vector<Object> objectList;
	Room(string rName);
	~Room();
	void printRooms();
	void printFeatures();
	void printObjects();
	void readDesc(int i,string s);
};

