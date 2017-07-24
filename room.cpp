#include "room.hpp"

Room::Room(int id, string name){//, string shortDesc, string longDesc) {
    this->id = id;
    this->name = name;
    //this->shortDesc = shortDesc;
    //this->longDesc = longDesc;
    this->visited = false;

    //the room path is built from the room name. it is trimmed down to remove any spaces
    this->roomPath = "src/rooms/"+ name + ".txt";
    this->roomPath.erase(remove_if(roomPath.begin(),roomPath.end(),::isspace),roomPath.end());
}

void Room::setId(int id) {
    this->id = id;
}

void Room::setName(string name) {
    this->name = name;
}

void Room::addAdjRoom(int roomId) {
    this->adjRooms.push_back(roomId);
}
/*
void Room::setShortDesc(string desc) {
    this->shortDesc = desc;
}

void Room::setLongDesc(string desc) {
    this->longDesc = desc;
}
*/



void Room::visitRoom() {
    this->visited = true;
}

int Room::getId() {
    return id;
}

string Room::getName() {
    return name;
}

vector<int> Room::getItems() {
    return items;
}

vector<int> Room::getDroppedItems() {
    return itemsDropped;
}
/*
string Room::getDescription() {
    if (!visited) {
        visited = true;
        return longDesc;
    } else {
        return shortDesc;
    }
}
*/

void Room::getDescription(int visit, string userCommand){
    bool linesWritten = false;

    //general command template [start|end + user command + room name + long|short]

    //[start|end
    string startCommand = "[start";
    string endCommand = "[end";
    string command;

    // + room name
    string trimmedRoomName = name;
    trimmedRoomName.erase(remove_if(trimmedRoomName.begin(),trimmedRoomName.end(), ::isspace), trimmedRoomName.end());
    // + user command
    command.append(userCommand);
    command.append(trimmedRoomName);

    // + long|short]
    if(!visit){
        command.append("long]");
    }
    else{
        command.append("short]");
    }

    //appending to the start end commands
    startCommand.append(command);
    endCommand.append(command);


    string readString;
    std::ifstream roomFile(roomPath.c_str());

    if(!roomFile.is_open()){
        cout << "Failed to open file" << endl;
    }
    
    while(std::getline(roomFile,readString)){
        if(readString.find(startCommand) != string::npos){
            while(std::getline(roomFile,readString)){
                if(readString.find(endCommand) != string::npos){
                    break;
                }
                else{
                cout << readString << endl;
                linesWritten = true;
                }                       
            }
            visited = true;
        }
    }

    if(!linesWritten){
        cout << "Failed to find starting point" << endl;
    }


}

bool Room::isVisited() {
    return visited;
}

