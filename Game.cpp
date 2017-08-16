#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include <fstream>
#include <stdlib.h>

#include "Game.hpp"
#include "Parse.hpp"

#include <unordered_map>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;


void Game::addRoom(Room room) {
    rooms.push_back(room);

    // If the room being added is the first room (has id of 1), then set
    // curRoom to that room
    //if (room.getId() == 1) {
    //    curRoom = &room;
    //}

}

void Game::addItem(string item) {
    items.push_back(item);
}

void Game::addToInventory(string item) {
    inventory.push_back(item);
}

void Game::removeFromInv(string item) {
    inventory.erase(std::remove(inventory.begin(), inventory.end(), item), inventory.end());
}

vector<string> Game::getInventory() {
    return inventory;
}

bool Game::inInventory(string item) {
    int invSize = inventory.size();
    for (int i = 0; i < invSize; i++) {
        if (strcmp(inventory[i].c_str(), item.c_str()) == 0) {
            return true;
        }
    }
    return false;
}

void Game::clearInv(){
    inventory.clear();
}

void Game::readHelpInfo(){
    string line;
    std::ifstream infile ("helpdata");
    if(infile.is_open()){
        while(getline(infile,line)){
            helpInfo.push_back(line);
        }
        infile.close();
    }
    else{
        cout << "unable to open file" << endl;
    }
}

vector<string> Game::getHelpInfo(){
    return helpInfo;
}

void Game::readItemInfo(){
    vector<string> data;
    string line;
    std::ifstream infile ("itemdata");
    if(infile.is_open()){
        while(getline(infile,line)){
            data.push_back(line);
        }
        infile.close();
    }

    for (int i = 0; i < data.size(); i+=2){
         itemInfo.insert({data[i],data[i+1]});
    }
    
    for (std::pair<std::string, string> element : itemInfo)
        std::cout << element.first << " :: " << element.second << std::endl;
    

}
std::unordered_map<string,string> Game::getItemInfo(){
    return itemInfo;
}

void Game::loadFiles() {
    DIR* curDir;
    struct dirent *fileInDir;
    curDir = opendir("./rooms");
    int intBuffer;
    string stringBuffer;

    if (curDir > 0) {
        while ((fileInDir = readdir(curDir)) != NULL) {
            string prefix = "./rooms/";
            string roomName = fileInDir->d_name;

            if (roomName[0] == '.') {
                continue;
            }

            string fileLoc = prefix + roomName;
            std::ifstream infile;
            infile.open(fileLoc);
            Room newRoom;

            // get id
            //infile >> intBuffer;
            getline(infile, stringBuffer);
            intBuffer = atoi(stringBuffer.c_str());
            newRoom.setId(intBuffer);

            // get name
            //infile >> stringBuffer;
            getline(infile, stringBuffer);
            newRoom.setName(stringBuffer);

            // get north exit
            //infile >> intBuffer;
            getline(infile, stringBuffer);
            intBuffer = atoi(stringBuffer.c_str());
            newRoom.addNorth(intBuffer);

            // get south exit
            getline(infile, stringBuffer);
            intBuffer = atoi(stringBuffer.c_str());
            newRoom.addSouth(intBuffer);

            // get east exit
            getline(infile, stringBuffer);
            intBuffer = atoi(stringBuffer.c_str());
            newRoom.addEast(intBuffer);

            // get west exit
            getline(infile, stringBuffer);
            intBuffer = atoi(stringBuffer.c_str());
            newRoom.addWest(intBuffer);

            // get north exit condition
            //infile >> stringBuffer;
            getline(infile, stringBuffer);
            newRoom.setNorthExitStatus(stringBuffer);

            // get south exit condition
            getline(infile, stringBuffer);
            newRoom.setSouthExitStatus(stringBuffer);

            // get east exit condition
            getline(infile, stringBuffer);
            newRoom.setEastExitStatus(stringBuffer);

            // get west exit condition
            getline(infile, stringBuffer);
            newRoom.setWestExitStatus(stringBuffer);

            // get short description
            getline(infile, stringBuffer);
            newRoom.setShortDesc(stringBuffer);

            // get long description
            getline(infile, stringBuffer);
            newRoom.setLongDesc(stringBuffer);

            // get feature 1 response
            getline(infile, stringBuffer);
            newRoom.setFeature1Response(stringBuffer);

            // get feature 2 response
            getline(infile, stringBuffer);
            newRoom.setFeature2Response(stringBuffer);

            // get feature 1 key
            getline(infile, stringBuffer);
            newRoom.setFeature1Key(stringBuffer);

            // get feature 2 key
            getline(infile, stringBuffer);
            newRoom.setFeature2Key(stringBuffer);

            // get item
            getline(infile, stringBuffer);
            newRoom.addStartingItem(stringBuffer);

            addRoom(newRoom);
            infile.close();
        }
    }
}

Room* Game::getCurRoom() {
    int numOfRooms = rooms.size();
    for (int i = 0; i < numOfRooms; i++) {
        if (rooms[i].getId() == curRoom) {
            return &rooms[i];
        }
    }
}

void Game::play() {//cout << "Welcome Bird Spy View." << endl;
    //cout << "You are an intrepid explorer trying to figure out what to do for the weekend. You aren’t too much of an outdoors person but you have been hearing stories of people being attacked by owls at a relatively close state park. Not only that, but there was a tremor at the park a few weeks ago. For most people this would dissuade them from visiting, but you feel like embracing the thrill of danger so you decide to head out." << endl;


    // Testing file loading functionality
    /*
    for (int i = 0; i < numOfRooms; i++) {
        cout << "New Room" << endl;
        cout << rooms[i].getId() << endl;
        cout << rooms[i].getName() << endl;
        cout << rooms[i].getNorth() << endl;
        cout << rooms[i].getSouth() << endl;
        cout << rooms[i].getEast() << endl;
        cout << rooms[i].getWest() << endl;
        cout << rooms[i].getNorthExitStatus() << endl;
        cout << rooms[i].getSouthExitStatus() << endl;
        cout << rooms[i].getEastExitStatus() << endl;
        cout << rooms[i].getWestExitStatus() << endl;
        cout << rooms[i].getShortDesc() << endl;
        cout << rooms[i].getLongDesc() << endl;
        cout << rooms[i].getFeature1Key() << endl;
        cout << rooms[i].getFeature2Key() << endl;
        cout << rooms[i].getItem() << endl << endl;
    }
     */

    // Create parser to interpret the user's commands
    Parse parser;
    // Load all of the room information in the room files into memory
    loadFiles();
    // Load helpdata file
    readHelpInfo();
    // Load itemdata file
    readItemInfo();
    // Initialize previousRoom to 0 so that it is different from the current room,
    // so that the description of the current room is displayed at the beginning of the
    // game loop
    int previousRoom = 0;
    // Set current room to Entrance
    curRoom = 1;

    // Main gameplay loop that runs until the user completes the game, or the user enters "exit"
    while (!isFinished) {
        Room *curRoom = getCurRoom();
        int curRoomId = curRoom->getId();

        // Print name of current room
        cout << endl << "Current room: " << curRoom->getName() << endl;

        // If the user does not change rooms through their command, they should not get the
        // the description again
        if (previousRoom != curRoomId) {
            cout << curRoom->getDescription() << endl;
        }
        previousRoom = curRoomId;

        cout << "What would you like to do?" << endl;
        // Get the user's input and pass it to the parser
        memset(userInput, '\0', 256);
        cin.getline(userInput, 255);
        parser.parseInput(*this, curRoom, userInput);

        // Implement parser
        if (strstr(userInput, "exit")) {
            isFinished = true;
        }
    }
}