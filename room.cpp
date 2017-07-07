#include "room.hpp"
#include <iostream> 

#include <vector>
#include <algorithm>

Room::Room(string rName)
{
	roomName = rName;
	visited = false;
	roomDesc = "Room1.txt";

}

void Room::printRooms()
{
	for (int i = 0; i < static_cast<signed int>(roomList.size()); i++){
		cout << roomList[i].roomName << endl;
	}
}

void Room::printFeatures()
{
	for (int i = 0; i < static_cast<signed int>(featureList.size()); i++) {
		cout << featureList[i].featureName << endl;
	}
}

void Room::printObjects()
{
	for (int i = 0; i < static_cast<signed int>(objectList.size()); i++) {
		cout << objectList[i].objectName << endl;
	}
}

void Room::readDesc(int i,string s)
{

	
	//Building the start and end markers
	string startCommand = "[start";
	string endCommand = "[end";
	
	string command;
	command.append(s);
	command.append(roomName);
	if(i == 0){
		command.append("long]");
	}
	else{
		command.append("short]");
	}

	startCommand.append(command);
	endCommand.append(command);

	string readString;
	ifstream roomFile(roomDesc);
	if(!roomFile.is_open()){
		cout << "Faild to open file" << endl;
	}
	
	while(std::getline(roomFile,readString)){
		if(readString.find(startCommand) != string::npos){
			while(std::getline(roomFile,readString)){
				if(readString.find(endCommand) != string::npos){
					break;
				}
				else{
				cout << readString << endl;
				}						
			}
			visited = true;
		}
	}



}



Room::~Room()
{
}
