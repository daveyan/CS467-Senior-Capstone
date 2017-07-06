#include "Room.hpp"
#include <iostream>


Room::Room() 
{
}

Room::Room(std::string rName)
{
	roomName = rName;
	visited = 0;
}

void Room::printRooms()
{
	for (int i = 0; i < static_cast<signed int>(roomList.size()); i++){
		std::cout << roomList[i].roomName << std::endl;
	}
}

void Room::printFeatures()
{
	for (int i = 0; i < static_cast<signed int>(featureList.size()); i++) {
		std::cout << featureList[i].featureName << std::endl;
	}
}

void Room::printObjects()
{
	for (int i = 0; i < static_cast<signed int>(objectList.size()); i++) {
		std::cout << objectList[i].objectName << std::endl;
	}
}

void Room::readDesc(int i)
{
	std::string readString;
	std::ifstream roomFile;
	roomFile.open(roomDesc);

	if (roomFile.is_open()) {
		while (!roomFile.eof()) {
			std::getline(roomFile, readString);
			if (i == 0) {
				if (readString == "[start" + roomName + "long]") {
					while (readString != "[end" + roomName + "long]") {
						std::getline(roomFile, readString);
						if (readString == "[end" + roomName + "long]") {
							break;
						}
						else {
							std::cout << readString << std::endl;
						}
					}

				}
				visited = 1;
			}
			else {
				if (readString == "[start" + roomName + "short]") {
					while (readString != "[end" + roomName + "short]") {
						std::getline(roomFile, readString);
						if (readString == "[end" + roomName + "short]") {
							break;
						}
						else {
							std::cout << readString << std::endl;
						}
					}

				}
			}


		}
		roomFile.close();
	}
	else {
		std::cout << "Unable to open file\n";
	}
}



Room::~Room()
{
}
