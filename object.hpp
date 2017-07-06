#pragma once
#include "Feature.hpp"
#include "Object.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>


class Room
{
public:
	int visited;
	std::string roomName;
	std::string roomDesc = "AllRooms.txt";
	std::vector<Room> roomList;
	std::vector<Feature> featureList;
	std::vector<Object> objectList;
	Room(std::string rName);
	Room();
	~Room();
	void printRooms();
	void printFeatures();
	void printObjects();
	void readDesc(int i);
};

