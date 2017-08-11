#include "Room.hpp"

Room::Room(int id, string name){ // ,string shortDesc, string longDesc) {
	this->id = id;
	this->name = name;
	this->visited = false;
	//this->shortDesc = shortDesc;
	//this->longDesc = longDesc;
	this->roomPath = "src/rooms/"+ name + ".txt";
    this->roomPath.erase(remove_if(roomPath.begin(),roomPath.end(),::isspace),roomPath.end());
	
}

Room::Room() {
	id = -1;
	name = " ";
	//shortDesc = " ";
	//longDesc = " ";
	visited = false;
}

void Room::setId(int id) {
	this->id = id;
}

void Room::setName(string name) {
	this->name = name;
}

void Room::addNorth(int roomId) {
	north = roomId;
}

void Room::addSouth(int roomId) {
	south = roomId;
}

void Room::addEast(int roomId) {
	east = roomId;
}

void Room::addWest(int roomId) {
	west = roomId;
}

void Room::setNorthExitStatus(string status) {
    northExitStatus = status;
}

void Room::setSouthExitStatus(string status) {
    southExitStatus = status;
}

void Room::setEastExitStatus(string status) {
    eastExitStatus = status;
}

void Room::setWestExitStatus(string status) {
    westExitStatus = status;
}

void Room::setShortDesc(string desc) {
    this->shortDesc = desc;
}

void Room::setLongDesc(string desc) {
    this->longDesc = desc;
}

string Room::getShortDesc() {
    return shortDesc;
}

string Room::getLongDesc() {
    return longDesc;
}

void Room::visitRoom() {
	this->visited = true;
}

void Room::addItem(string item) {
    items.push_back(item);
}

int Room::getId() {
	return id;
}

int Room::getNorth() {
	return north;
}

int Room::getSouth() {
	return south;
}

int Room::getEast() {
	return east;
}

int Room::getWest() {
	return west;
}

string Room::getNorthExitStatus() {
    return northExitStatus;
}

string Room::getSouthExitStatus() {
    return southExitStatus;
}

string Room::getEastExitStatus() {
    return eastExitStatus;
}

string Room::getWestExitStatus() {
    return westExitStatus;
}

string Room::getName() {
	return name;
}

vector<string> Room::getItems() {
    return items;
}

vector<string> Room::getDroppedItems() {
    return itemsDropped;
}

string Room::getDescription() {
    if (!visited) {
        visited = true;
        return longDesc;
    } else {
        return shortDesc;
    }
}

string Room::getFeature1Response() {
    return feature1Response;
}

string Room::getFeature2Response() {
    return feature2Response;
}


void Room::setFeature1Response(string resp) {
    feature1Response = resp;
}

void Room::setFeature2Response(string resp) {
    feature2Response = resp;
}

void Room::setFeature1Key(string key) {
    feature1Key = key;
}

void Room::setFeature2Key(string key) {
    feature2Key = key;
}

string Room::getFeature1Key() {
    return feature1Key;
}

string Room::getFeature2Key() {
    return feature2Key;
}

bool Room::isVisited() {
	return visited;
}

void Room::clearRoomInv(){
    items.clear();
}

void Room::setVisited(bool v){
    visited = v;
}

string Room::getDesc(string userCommand){
    bool linesWritten = false;

    //general command template [start|end + long|short|Feature1|Feature2]

    //[start|end
    string startCommand = "[start";
    string endCommand = "[end";
    string command;

    //long|short|Feature1|Feature2
    command.append(userCommand);
    command.append("]");
    
    //appending start end commands 
    startCommand.append(command);
    endCommand.append(command);


    string readString;
    std::ifstream roomFile(roomPath.c_str());

    if(!roomFile.is_open()){
        cout << "Failed to open file" << endl;
        return "Error";
    }
    
    string allread = "";

    while(std::getline(roomFile,readString)){
        if(readString.find(startCommand) != string::npos){
            while(std::getline(roomFile,readString)){
                if(readString.find(endCommand) != string::npos){
                    break;
                }
                else{
                allread.append(readString);
                linesWritten = true;
                }                       
            }
           
        }
    }

    if(!linesWritten){
        cout << "Failed to find starting point" << endl;
        return "Error";
    }


    return allread;
}

void Room::removeItem(string item) {
    items.erase(std::remove(items.begin(), items.end(), item), items.end());
}
