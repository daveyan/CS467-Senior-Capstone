#include <iostream>
#include <string>
#include <string.h>
#include <fstream>

#include "Parse.hpp"

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

Parse::Parse() {
    //popActions();
    //popEntranceItemNouns();
}

/*
void Parse::popActions() {
    actions.push_back("pick");
    actions.push_back("pick up");
    actions.push_back("snag");
    actions.push_back("lift");
    actions.push_back("scoop");
    actions.push_back("grab");
    actions.push_back("inspect");
    actions.push_back("check");
    actions.push_back("read");
    actions.push_back("open");
}

void Parse::popEntranceItemNouns() {
    entranceItemNouns.push_back("bar");
    entranceItemNouns.push_back("pipe");
    entranceItemNouns.push_back("rod");
}
*/
Room* Parse::findRoom(Game &curGame, string name) {
    for (int i = 0; i < curGame.rooms.size(); i++) {
        if (strstr(name.c_str(), curGame.rooms[i].getName().c_str())) {
            return &curGame.rooms[i];
        }
    }
}

bool Parse::checkForMatch(vector<string> collection1, vector<string> collection2, string userInput) {
    int sizeOfCol1 = collection1.size();
    int sizeOfCol2 = collection2.size();

    for (int i = 0; i < sizeOfCol1; i++) {
        if (strstr(userInput.c_str(), collection1[i].c_str()) != NULL) {
            for (int j = 0; j < sizeOfCol2; j++) {
                if (strstr(userInput.c_str(), collection2[j].c_str()) != NULL) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Parse::checkForMatch(vector<string> collection1, string userInput) {
    int sizeOfCol1 = collection1.size();

    for (int i = 0; i < sizeOfCol1; i++) {
        if (strstr(userInput.c_str(), collection1[i].c_str()) != NULL) {
            return true;
        }
    }
    return false;
}

void Parse::parseEntrance(Game &curGame, Room *curRoom, string userInput) {
    // If the user wants to go north
    // Find the connecting room's name
    string north_room;
    for (int i = 0; i < curGame.rooms.size(); i++) {
        if (curGame.rooms[i].getId() == curRoom->getNorth()) {
            north_room = curGame.rooms[i].getName();
        }
    }
    if (strstr(userInput.c_str(), "go north") != NULL || strstr(userInput.c_str(), "north") != NULL ||
        strstr(userInput.c_str(), north_room.c_str()) != NULL) {
        //if (!curGame.inInventory("bar")) {
        if (curRoom->hasItem == false) {
            cout << "You should have a bar to pry the door open..." << endl;
        } else {
            cout << "The door is now to open to go through since you pried it open with the metal bar" << endl;
            curGame.curRoom = curRoom->getNorth();
        }
    // If the user wants to go south
    } else if (strstr(userInput.c_str(), "go south") != NULL || strstr(userInput.c_str(), "south") != NULL) {
        cout << "There is nowhere south of here" << endl;
    // If the user wants to go east
    } else if (strstr(userInput.c_str(), "go east") != NULL || strstr(userInput.c_str(), "east") != NULL) {
        cout << "There is nowhere east of here" << endl;
    // If the user wants to go west
    } else if (strstr(userInput.c_str(), "go west") != NULL || strstr(userInput.c_str(), "west") != NULL) {
        cout << "There is nowhere west of here" << endl;
    // Check if the user wants to pick up the bar
    } else if (checkForMatch(actions, entranceItemNouns, userInput)) {
        // user wants to grab bar
        // Check if already in inventory
        //if (curGame.inInventory("bar")) {
        if (curRoom->hasItem == true) {
            cout << "You already have that in your inventory." << endl;
        } else {        
            curGame.addToInventory("bar");
            curRoom->item = "null";
            curRoom->hasItem = true;
            cout << "You have grabbed the metal bar." << endl;

        }
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseVestibule(Game &curGame, Room *curRoom, string userInput) {
    
    // Get the names of each connecting room
    string north_room, south_room, east_room;
    for (int i = 0; i < curGame.rooms.size(); i++) {
        if (curGame.rooms[i].getId() == curRoom->getNorth()) {
            north_room = curGame.rooms[i].getName();
        }
        if (curGame.rooms[i].getId() == curRoom->getSouth()) {
            south_room = curGame.rooms[i].getName();
        }
        if (curGame.rooms[i].getId() == curRoom->getEast()) {
            east_room = curGame.rooms[i].getName();
        }
    }
    // If the user wants to go north
    if (strstr(userInput.c_str(), "go north") != NULL || strstr(userInput.c_str(), "north") != NULL ||
        strstr(userInput.c_str(), north_room.c_str()) != NULL) {
        
        // Need keycard
        if (curRoom->hasItem == false) {
            cout << "You need a keycard to go through the door open..." << endl;
        } else {
            cout << "Keycard used to unlock the door" << endl;
            curGame.curRoom = curRoom->getNorth();
        }

    } else if (strstr(userInput.c_str(), "go south") != NULL || strstr(userInput.c_str(), "south") != NULL ||
        strstr(userInput.c_str(), south_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getSouth();

    } else if (strstr(userInput.c_str(), "go east") != NULL || strstr(userInput.c_str(), "east") != NULL ||
        strstr(userInput.c_str(), east_room.c_str()) != NULL) {
        
        // Need flashlight
        if (curRoom->hasSecondItem == false) {
            cout << "You should have a flashlight before going into such a dark room..." << endl;
        } else {
            cout << "You have the illumination necessary to go east" << endl;
            curGame.curRoom = curRoom->getEast();
        }

    } else if (strstr(userInput.c_str(), "go west") != NULL || strstr(userInput.c_str(), "west") != NULL) {
        cout << "There is nowhere west of here" << endl;

    } else if (checkForMatch(actions, vestibuleFlashlightNouns, userInput)) {
        if (curGame.inInventory("flashlight")) {
            cout << "You already have that in your inventory." << endl;
        } else {        
            curGame.addToInventory("flashlight");
            curRoom->item = "null";
            curRoom->hasSecondItem = true;
            cout << "You have grabbed the flashlight." << endl;
        }
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseMechanicalRoom(Game &curGame, Room *curRoom, string userInput) {
    
    // Get the names of each connecting room
    string east_room, west_room;
    for (int i = 0; i < curGame.rooms.size(); i++) {
        if (curGame.rooms[i].getId() == curRoom->getEast()) {
            east_room = curGame.rooms[i].getName();
        }
        if (curGame.rooms[i].getId() == curRoom->getWest()) {
            west_room = curGame.rooms[i].getName();
        }
    }

    if (strstr(userInput.c_str(), "go north") != NULL || strstr(userInput.c_str(), "north") != NULL) {
        cout << "There is nowhere north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL || strstr(userInput.c_str(), "south") != NULL) {
        cout << "There is nowhere south of here" << endl;
    } else if (strstr(userInput.c_str(), "go east") != NULL || strstr(userInput.c_str(), "east") != NULL ||
        strstr(userInput.c_str(), east_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getEast();
    } else if (strstr(userInput.c_str(), "go west") != NULL || strstr(userInput.c_str(), "west") != NULL ||
        strstr(userInput.c_str(), west_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getWest();
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseGarage(Game &curGame, Room *curRoom, string userInput) {

    // Get the names of each connecting room
    string west_room;
    for (int i = 0; i < curGame.rooms.size(); i++) {
        if (curGame.rooms[i].getId() == curRoom->getWest()) {
            west_room = curGame.rooms[i].getName();
        }
    }

    if (strstr(userInput.c_str(), "go north") != NULL || strstr(userInput.c_str(), "north") != NULL) {
        cout << "There is nowhere north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL || strstr(userInput.c_str(), "south") != NULL) {
        cout << "There is nowhere south of here" << endl;
    } else if (strstr(userInput.c_str(), "go east") != NULL || strstr(userInput.c_str(), "east") != NULL) {
        //if (!curGame.inInventory("opener")) {
        if (curRoom->hasItem == false) {
            cout << "Looks like a garage door opener is needed to leave this way..." << endl;
        } else {
            cout << "You should have opened the garage door, sped out, and now you are free to tell the world about what you learned!" << endl;
            curGame.isFinished = true;
        }
    } else if (strstr(userInput.c_str(), "go west") != NULL || strstr(userInput.c_str(), "west") != NULL ||
        strstr(userInput.c_str(), west_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getWest();
    } else if (checkForMatch(actions, garageItemNouns, userInput)) {
        // user wants to grab keycard
        Room* vestibule = findRoom(curGame, "Vestibule");
        //if (curGame.inInventory("keycard")) {
        if (vestibule->hasItem == true) {
            cout << "You already have that in your inventory." << endl;
        } else {        
            curGame.addToInventory("keycard");
            vestibule->hasItem = true;
            curRoom->item = "null";
            cout << "You have grabbed the keycard." << endl;
        }
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseBreakRoom(Game &curGame, Room *curRoom, string userInput) {

    // Get the names of each connecting room
    string east_room, west_room;
    for (int i = 0; i < curGame.rooms.size(); i++) {
        if (curGame.rooms[i].getId() == curRoom->getEast()) {
            east_room = curGame.rooms[i].getName();
        }
        if (curGame.rooms[i].getId() == curRoom->getWest()) {
            west_room = curGame.rooms[i].getName();
        }
    }

    if (strstr(userInput.c_str(), "go north") != NULL || strstr(userInput.c_str(), "north") != NULL) {
        cout << "There is nowhere north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL || strstr(userInput.c_str(), "south") != NULL) {
        cout << "There is nowhere south of here" << endl;
    } else if (strstr(userInput.c_str(), "go east") != NULL || strstr(userInput.c_str(), "east") != NULL ||
        strstr(userInput.c_str(), east_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getEast();
    } else if (strstr(userInput.c_str(), "go west") != NULL || strstr(userInput.c_str(), "west") != NULL ||
        strstr(userInput.c_str(), west_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getWest();
    } else if (checkForMatch(actions, breakroomItemNouns, userInput)) {
        // user wants to grab hat
        Room* computerlab = findRoom(curGame, "Computer Lab");
        //if (curGame.inInventory("hat")) {
        if (computerlab->hasItem == true) {
            cout << "You already have that in your inventory." << endl;
        } else {        
            curGame.addToInventory("hat");
            curRoom->item = "null";
            computerlab->hasItem = true;
            cout << "You have grabbed the hard hat." << endl;
        }
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseBathroom(Game &curGame, Room *curRoom, string userInput) {

    // Get the names of each connecting room
    string east_room;
    for (int i = 0; i < curGame.rooms.size(); i++) {
        if (curGame.rooms[i].getId() == curRoom->getEast()) {
            east_room = curGame.rooms[i].getName();
        }
    }

    if (strstr(userInput.c_str(), "go north") != NULL || strstr(userInput.c_str(), "north") != NULL) {
        cout << "There is nowhere north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL || strstr(userInput.c_str(), "south") != NULL) {
        cout << "There is nowhere south of here" << endl;
    } else if (strstr(userInput.c_str(), "go east") != NULL || strstr(userInput.c_str(), "east") != NULL ||
        strstr(userInput.c_str(), east_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getEast();
    } else if (strstr(userInput.c_str(), "go west") != NULL || strstr(userInput.c_str(), "west") != NULL) {
        cout << "There is nowhere west of here" << endl;
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseLounge(Game &curGame, Room *curRoom, string userInput) {

    // Get the names of each connecting room
    string north_room, south_room, east_room, west_room;
    for (int i = 0; i < curGame.rooms.size(); i++) {
        if (curGame.rooms[i].getId() == curRoom->getNorth()) {
            north_room = curGame.rooms[i].getName();
        }
        if (curGame.rooms[i].getId() == curRoom->getSouth()) {
            south_room = curGame.rooms[i].getName();
        }
        if (curGame.rooms[i].getId() == curRoom->getEast()) {
            east_room = curGame.rooms[i].getName();
        }
        if (curGame.rooms[i].getId() == curRoom->getWest()) {
            west_room = curGame.rooms[i].getName();
        }
    }

    if (strstr(userInput.c_str(), "go north") != NULL || strstr(userInput.c_str(), "north") != NULL ||
        strstr(userInput.c_str(), north_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getNorth();
    } else if (strstr(userInput.c_str(), "go south") != NULL || strstr(userInput.c_str(), "south") != NULL ||
        strstr(userInput.c_str(), south_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getSouth();
    } else if (strstr(userInput.c_str(), "go east") != NULL || strstr(userInput.c_str(), "east") != NULL ||
        strstr(userInput.c_str(), east_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getEast();
    } else if (strstr(userInput.c_str(), "go west") != NULL || strstr(userInput.c_str(), "west") != NULL ||
        strstr(userInput.c_str(), west_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getWest();
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseOffice(Game &curGame, Room *curRoom, string userInput) {

    // Get the names of each connecting room
    string west_room;
    for (int i = 0; i < curGame.rooms.size(); i++) {
        if (curGame.rooms[i].getId() == curRoom->getWest()) {
            west_room = curGame.rooms[i].getName();
        }
    }

    if (strstr(userInput.c_str(), "go north") != NULL || strstr(userInput.c_str(), "north") != NULL) {
        cout << "There is nowhere north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL || strstr(userInput.c_str(), "south") != NULL) {
        cout << "There is nowhere south of here" << endl;
    } else if (strstr(userInput.c_str(), "go east") != NULL || strstr(userInput.c_str(), "east") != NULL) {
        cout << "There is nowhere east of here" << endl;
    } else if (strstr(userInput.c_str(), "go west") != NULL || strstr(userInput.c_str(), "west") != NULL ||
        strstr(userInput.c_str(), west_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getWest();
    } else if (checkForMatch(actions, officeItemNouns, userInput)) {
        // user wants to grab file
        //if (curGame.inInventory("file")) {
        if (curRoom->hasItem == true) {
            cout << "You already have that in your inventory." << endl;
        } else {        
            curGame.addToInventory("file");
            curRoom->item = "null";
            curRoom->hasItem = true;
            cout << "You have grabbed the file." << endl;
        }
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseComputerLab(Game &curGame, Room *curRoom, string userInput) {

    // Get the names of each connecting room
    string north_room, south_room, east_room, west_room;
    for (int i = 0; i < curGame.rooms.size(); i++) {
        if (curGame.rooms[i].getId() == curRoom->getNorth()) {
            north_room = curGame.rooms[i].getName();
        }
        if (curGame.rooms[i].getId() == curRoom->getSouth()) {
            south_room = curGame.rooms[i].getName();
        }
        if (curGame.rooms[i].getId() == curRoom->getEast()) {
            east_room = curGame.rooms[i].getName();
        }
        if (curGame.rooms[i].getId() == curRoom->getWest()) {
            west_room = curGame.rooms[i].getName();
        }
    }

    if (strstr(userInput.c_str(), "go north") != NULL || strstr(userInput.c_str(), "north") != NULL ||
        strstr(userInput.c_str(), north_room.c_str()) != NULL) {
        // Need postit
        //if (!curGame.inInventory("postit")) {
        if (curRoom->hasSecondItem == false) {
            cout << "You need the passcode to open the door. Maybe it is written down somewhere..." << endl;
        } else {
            cout << "You use the passcode to go through the door" << endl;
            curGame.curRoom = curRoom->getNorth();
        }
    } else if (strstr(userInput.c_str(), "go south") != NULL || strstr(userInput.c_str(), "south") != NULL ||
        strstr(userInput.c_str(), south_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getSouth();
    } else if (strstr(userInput.c_str(), "go east") != NULL || strstr(userInput.c_str(), "east") != NULL ||
        strstr(userInput.c_str(), east_room.c_str()) != NULL) {
        // Need hard had
        //if (!curGame.inInventory("hat")) {
        if (curRoom->hasItem == false) {
            cout << "It sounds dangerous in there. Maybe you should have some protective equipment..." << endl;
        } else {
            cout << "With the hard hat on, you move forward..." << endl;
            curGame.curRoom = curRoom->getEast();
        }
    } else if (strstr(userInput.c_str(), "go west") != NULL || strstr(userInput.c_str(), "west") != NULL ||
        strstr(userInput.c_str(), west_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getWest();
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseLiveRobotAnimals(Game &curGame, Room *curRoom, string userInput) {

     // Get the names of each connecting room
    string east_room, west_room;
    for (int i = 0; i < curGame.rooms.size(); i++) {
        if (curGame.rooms[i].getId() == curRoom->getEast()) {
            east_room = curGame.rooms[i].getName();
        }
        if (curGame.rooms[i].getId() == curRoom->getWest()) {
            west_room = curGame.rooms[i].getName();
        }
    }

    if (strstr(userInput.c_str(), "go north") != NULL || strstr(userInput.c_str(), "north") != NULL) {
        cout << "There is nowhere north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL || strstr(userInput.c_str(), "south") != NULL) {
        cout << "There is nowhere south of here" << endl;
    } else if (strstr(userInput.c_str(), "go east") != NULL || strstr(userInput.c_str(), "east") != NULL ||
        strstr(userInput.c_str(), east_room.c_str()) != NULL) {
        
        // Need net
        if (curRoom->hasItem == false) {
            cout << "Something should be used to secure the area before moving forward..." << endl;
        } else {
            cout << "The net was thrown, capturing the owl, allowing you to move forward" << endl;
            curGame.curRoom = curRoom->getEast();
        }
    } else if (strstr(userInput.c_str(), "go west") != NULL || strstr(userInput.c_str(), "west") != NULL ||
        strstr(userInput.c_str(), west_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getWest();
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseMockForest(Game &curGame, Room *curRoom, string userInput) {

    // Get the names of each connecting room
    string west_room;
    for (int i = 0; i < curGame.rooms.size(); i++) {
        if (curGame.rooms[i].getId() == curRoom->getWest()) {
            west_room = curGame.rooms[i].getName();
        }
    }

    if (strstr(userInput.c_str(), "go north") != NULL || strstr(userInput.c_str(), "north") != NULL) {
        cout << "There is nowhere to the north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL || strstr(userInput.c_str(), "south") != NULL) {
        cout << "There is nowhere to the south of here" << endl;
    } else if (strstr(userInput.c_str(), "go east") != NULL || strstr(userInput.c_str(), "east") != NULL) {
        cout << "There is nowhere to the east of here" << endl;
    } else if (strstr(userInput.c_str(), "go west") != NULL || strstr(userInput.c_str(), "west") != NULL ||
        strstr(userInput.c_str(), west_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getWest();
    } else if (checkForMatch(actions, mockforestItemNouns, userInput)) {
        
        // user wants to grab postit
        Room* computerLab = findRoom(curGame, "Computer Lab");
        if (computerLab->hasSecondItem == true) {
            cout << "You already have that in your inventory." << endl;
        } else {        
            curGame.addToInventory("postit");
            curRoom->item = "null";
            computerLab->hasSecondItem = true;
            cout << "You have grabbed the postit." << endl;
        }
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseTaxidermy(Game &curGame, Room *curRoom, string userInput) {

    // Get the names of each connecting room
    string east_room, west_room;
    for (int i = 0; i < curGame.rooms.size(); i++) {
        if (curGame.rooms[i].getId() == curRoom->getEast()) {
            east_room = curGame.rooms[i].getName();
        }
        if (curGame.rooms[i].getId() == curRoom->getWest()) {
            west_room = curGame.rooms[i].getName();
        }
    }

    if (strstr(userInput.c_str(), "go north") != NULL || strstr(userInput.c_str(), "north") != NULL) {
        cout << "There is nowhere north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL || strstr(userInput.c_str(), "south") != NULL) {
        cout << "There is nowhere south of here" << endl;
    } else if (strstr(userInput.c_str(), "go east") != NULL || strstr(userInput.c_str(), "east") != NULL ||
        strstr(userInput.c_str(), east_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getEast();
    } else if (strstr(userInput.c_str(), "go west") != NULL || strstr(userInput.c_str(), "west") != NULL ||
        strstr(userInput.c_str(), west_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getWest();
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseRobotAssemblyRoom(Game &curGame, Room *curRoom, string userInput) {

    // Get the names of each connecting room
    string east_room, west_room;
    for (int i = 0; i < curGame.rooms.size(); i++) {
        if (curGame.rooms[i].getId() == curRoom->getEast()) {
            east_room = curGame.rooms[i].getName();
        }
        if (curGame.rooms[i].getId() == curRoom->getWest()) {
            west_room = curGame.rooms[i].getName();
        }
    }

    if (strstr(userInput.c_str(), "go north") != NULL || strstr(userInput.c_str(), "north") != NULL) {
        cout << "There is nowhere north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL || strstr(userInput.c_str(), "south") != NULL) {
        cout << "There is nowhere south of here" << endl;
    } else if (strstr(userInput.c_str(), "go east") != NULL || strstr(userInput.c_str(), "east") != NULL ||
        strstr(userInput.c_str(), east_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getEast();
    } else if (strstr(userInput.c_str(), "go west") != NULL || strstr(userInput.c_str(), "west") != NULL ||
        strstr(userInput.c_str(), west_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getWest();
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseMechanicalSupplyRoom(Game &curGame, Room *curRoom, string userInput) {

    // Get the names of each connecting room
    string east_room;
    for (int i = 0; i < curGame.rooms.size(); i++) {
        if (curGame.rooms[i].getId() == curRoom->getEast()) {
            east_room = curGame.rooms[i].getName();
        }
    }

    if (strstr(userInput.c_str(), "go north") != NULL || strstr(userInput.c_str(), "north") != NULL) {
        cout << "There is nowhere north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL || strstr(userInput.c_str(), "south") != NULL) {
        cout << "There is nowhere south of here" << endl;
    } else if (strstr(userInput.c_str(), "go east") != NULL || strstr(userInput.c_str(), "east") != NULL ||
        strstr(userInput.c_str(), east_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getEast();
    } else if (strstr(userInput.c_str(), "go west") != NULL || strstr(userInput.c_str(), "west") != NULL) {
        cout << "There is nowhere west of here" << endl;
    } else if (checkForMatch(actions, mechanicalsupplyItemNouns, userInput)) {
        // user wants to grab net
        Room* liveRobotAnimals = findRoom(curGame, "Live Robot Animals");
        //if (curGame.inInventory("net")) {
        if (liveRobotAnimals->hasItem == true) {
            cout << "You already have that in your inventory." << endl;
        } else {        
            curGame.addToInventory("net");
            curRoom->item = "null";
            liveRobotAnimals->hasItem = true;
            cout << "You have grabbed the exploding net." << endl;
        }
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseMonitoringRoom(Game &curGame, Room *curRoom, string userInput) {

    // Get the names of each connecting room
    string south_room;
    for (int i = 0; i < curGame.rooms.size(); i++) {
        if (curGame.rooms[i].getId() == curRoom->getSouth()) {
            south_room = curGame.rooms[i].getName();
        }
    }

    if (strstr(userInput.c_str(), "go north") != NULL || strstr(userInput.c_str(), "north") != NULL) {
        cout << "There is nowhere north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL || strstr(userInput.c_str(), "south") != NULL ||
        strstr(userInput.c_str(), south_room.c_str()) != NULL) {
        curGame.curRoom = curRoom->getSouth();
    } else if (strstr(userInput.c_str(), "go east") != NULL || strstr(userInput.c_str(), "east") != NULL) {
        cout << "There is nowhere east of here" << endl;
    } else if (strstr(userInput.c_str(), "go west") != NULL || strstr(userInput.c_str(), "west") != NULL) {
        cout << "There is nowhere west of here" << endl;
    } else if (checkForMatch(actions, monitoringroomItemNouns, userInput)) {
        // user wants to grab opener
        Room* garage = findRoom(curGame, "Garage");
        //if (curGame.inInventory("opener")) {
        if (garage->hasItem == true) {
            cout << "You already have that in your inventory." << endl;
        } else {        
            curGame.addToInventory("opener");
            curRoom->item = "null";
            garage->hasItem = true;
            cout << "You have grabbed the garage door opener." << endl;
        }
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseInput(Game &curGame, Room *curRoom, string userInput) {
    // If user wants to pick up a dropped item
    if (checkForMatch(actions, curRoom->getDroppedItems(), userInput)) {
        for (int i = 0; i < curRoom->getDroppedItems().size(); i++) {
            if (strstr(userInput.c_str(), curRoom->getDroppedItems()[i].c_str())) {
                cout << "You have grabbed the " << curRoom->getDroppedItems()[i] << " again." << endl;

                // Add to player inventory
                curGame.addToInventory(curRoom->getDroppedItems()[i]);

                // Remove from room's dropped items vector
                curRoom->removeItem(curRoom->getDroppedItems()[i]);
            }
        }
    }

    // Check inventory
    else if (strstr(userInput.c_str(), "inventory")) {
        cout << "Your inventory: " << endl;

        int invSize = curGame.inventory.size();
        for (int i = 0; i < invSize; i++) {
            cout << curGame.inventory[i] << endl;
        }
    }

    // Help command
    else if (strstr(userInput.c_str(), "help") ||strstr(userInput.c_str(), "Help")) {
    	cout << " >>> Help Information <<<" << endl;
    	for (int i = 0; i < curGame.getHelpInfo().size();i++){
    		cout << curGame.getHelpInfo()[i] <<endl;
    	}
    	
    }


    // Save game
    else if (strstr(userInput.c_str(), "savegame") ||strstr(userInput.c_str(), "Savegame")) {

        cout << ">>> Game Saved <<<" << endl;
        ofstream savefile;
        savefile.open ("savegame.txt");

        
        //Player Data
        //Writing current room index
        savefile << curGame.curRoom << endl;
        //Inventory Size
        savefile << curGame.inventory.size() << endl;
        //For all items in inventory, write to save.
        if(!curGame.inventory.empty()){
            for (int i = 0; i < curGame.inventory.size();i++){
                savefile << curGame.inventory[i] << endl;
            }
        }

        //Room Data
        for (int i = 0; i < curGame.rooms.size(); i++){
            //Writing the room name
            savefile << curGame.rooms[i].getName() << endl;
            //Write visit status
            savefile << curGame.rooms[i].isVisited() << endl;
            //Writing hasItem
            savefile << curGame.rooms[i].hasItem << endl;
            //Writing hasSecondItem
            savefile << curGame.rooms[i].hasSecondItem << endl;
            //Write room item
            savefile << curGame.rooms[i].item << endl;
            //Write number of dropped items
            savefile << curGame.rooms[i].getDroppedItems().size() << endl;
            if(!curGame.rooms[i].getDroppedItems().empty()){
                for (int j = 0; j <curGame.rooms[i].getDroppedItems().size(); j++){
                    savefile << curGame.rooms[i].getDroppedItems()[j] <<endl;
                }
            }
        }
         

        savefile.close();
    }

    // Load game
    else if (strstr(userInput.c_str(), "loadgame") ||strstr(userInput.c_str(), "Loadgame")) {

        cout << ">>> Game Loaded <<<" << endl;
        ifstream loadfile ("savegame.txt");

        if(!loadfile.fail()){

	        vector <string> loadfileData;
	        string s;
	        int data;
	        int lineNumber = 0;

	        //Read all the data from the save file line by line
	        while(std::getline(loadfile,s)){
	                loadfileData.push_back(s);
	            }

	        //Player Data
	        //room information
	        int loadRoomId = std::stoi(loadfileData[lineNumber]);
	        curGame.curRoom = loadRoomId;
	        lineNumber++;
	        //player inventory
	        int numItems = std::stoi(loadfileData[lineNumber]);
	        lineNumber++;
	        //clear the exisiting inventory
	        curGame.clearInv();
	        //write items to inventory
	        if(numItems != 0){
	            for (int i = 0; i < numItems; i++){
	                curGame.addToInventory(loadfileData[lineNumber+i]);
	            }
	        }
	        lineNumber += numItems;

	        //Room Data
	        for (int i = 0; i < curGame.rooms.size();i++){
	            curGame.rooms[i].clearDroppedItems();
	            curGame.rooms[i].item = "null";

	            //current position room name
	            lineNumber++;
	            //current position visited
	            curGame.rooms[i].setVisited(std::stoi(loadfileData[lineNumber]));
	            lineNumber++;
	            //current position hasItem
	            curGame.rooms[i].hasItem = std::stoi(loadfileData[lineNumber]);
	            lineNumber++;
	            //current position hasSecondItem
	            curGame.rooms[i].hasSecondItem = std::stoi(loadfileData[lineNumber]);
	            lineNumber++;
	            //current position roomItem
	            curGame.rooms[i].item = loadfileData[lineNumber];
	            lineNumber++;
	            //current position number of dropped item
	            int numDroppedItems = std::stoi(loadfileData[lineNumber]);
	            lineNumber++;
	            //current position adding each dropped item
	            if (numDroppedItems != 0){
	                for (int j = 0; j < numDroppedItems;j++){
	                    curGame.rooms[i].addItem(loadfileData[lineNumber]);
	                    lineNumber++;
	                }
	            }


	        }

	        loadfile.close();
    	}
    	else{
    		cout << "No save file exists" <<endl;
    	}
    }

    // Feature 1 interaction
    else if (strstr(userInput.c_str(), curRoom->getFeature1Key().c_str()) != NULL) {
        if (checkForMatch(actions, userInput)) {
            cout << curRoom->getFeature1Response() << endl;
        } else {
            cout << "Command not recognized" << endl;
        }

    // Feature 2 interaction
    } else if (strstr(userInput.c_str(), curRoom->getFeature2Key().c_str()) != NULL) {
        if (checkForMatch(actions, userInput)) {
            cout << curRoom->getFeature2Response() << endl;
        } else {
            cout << "Command not recognized" << endl;
        }
    }
    // Display Feature 1 or 2 descriptions as well as item description
    else if (strstr(userInput.c_str(), "look at") || strstr(userInput.c_str(), "Look at")) {
        
        /*
        // If user requests 1st room feature description
        if (strstr(userInput.c_str(), curRoom->getFeature1Key().c_str()) != NULL) {
            cout << curRoom->getFeature1Response() << endl;
        }

        // If user request 2nd room feature description
        if (strstr(userInput.c_str(), curRoom->getFeature2Key().c_str()) != NULL) {
            cout << curRoom->getFeature2Response() << endl;
        }
        */

        // If user requests description of item in room
        if (strstr(userInput.c_str(), curRoom->item.c_str())) {
            // Store the item in a local string
            string room_item = curRoom->item;
            for (std::pair<std::string, string> element : curGame.getItemInfo()){
                if(strstr(element.first.c_str(), room_item.c_str())){
                    cout << element.second << endl;
                }
            }
        }

        // If user requests description of an item in their inventory
        for (int i = 0; i < curGame.inventory.size(); i++) {
            if(strstr(userInput.c_str(), curGame.inventory[i].c_str())){
                // Store the item in a local string
                string inventory_item = curGame.inventory[i];
                for (std::pair<std::string, string> element : curGame.getItemInfo()){
                    if(strstr(element.first.c_str(), inventory_item.c_str())){
                        cout << element.second << endl;
                    }
                }
            }
        }

        // If not in inventory, check the current room's dropped items
        for (int i = 0; i < curRoom->getDroppedItems().size(); i++) {
            if (strstr(userInput.c_str(), curRoom->getDroppedItems()[i].c_str())) {
                // Store the item in a local string
                string dropped_item = curRoom->getDroppedItems()[i];
                for (std::pair<std::string, string> element : curGame.getItemInfo()){
                    if(strstr(element.first.c_str(), dropped_item.c_str())){
                        cout << element.second << endl;
                    }
                }
            }
        }
    }

     // User wants to repeat long-form room description
    else if (strstr(userInput.c_str(), "look") || strstr(userInput.c_str(), "Look")) {
        cout << endl << curRoom->getLongDesc() << endl;
    }
    // User wants to exit
    else if (strstr(userInput.c_str(), "exit") != NULL) {
        curGame.isFinished = true;

    // User wants to drop an item in a room
    } else if (strstr(userInput.c_str(), "drop") || strstr(userInput.c_str(), "Drop")) {
        cout << "You entered: " << userInput << endl;
        for (int i = 0; i < curGame.getInventory().size(); i++) {
            if (strstr(userInput.c_str(), curGame.getInventory()[i].c_str())) {
                cout << "You've dropped the " << curGame.getInventory()[i] << " in the " << curRoom->getName() << "." << endl;

                 // Add to curRoom's inventory
                curRoom->addItem(curGame.getInventory()[i]);

                // Remove from inventory
                curGame.removeFromInv(curGame.getInventory()[i]);
            }
        }

    // Parse command with respect to the current room
    } else {
        switch (curGame.curRoom) {
            case 1:
                parseEntrance(curGame, curRoom, userInput);
                break;
            case 2:
                parseVestibule(curGame, curRoom, userInput);
                break;
            case 3:
                parseMechanicalRoom(curGame, curRoom, userInput);
                break;
            case 4:
                parseGarage(curGame, curRoom, userInput);
                break;
            case 5:
                parseLounge(curGame, curRoom, userInput);
                break;
            case 6:
                parseBreakRoom(curGame, curRoom, userInput);
                break;
            case 7:
                parseBathroom(curGame, curRoom, userInput);
                break;
            case 8:
                parseOffice(curGame, curRoom, userInput);
                break;
            case 9:
                parseComputerLab(curGame, curRoom, userInput);
                break;
            case 10:
                parseTaxidermy(curGame, curRoom, userInput);
                break;
            case 11:
                parseRobotAssemblyRoom(curGame, curRoom, userInput);
                break;
            case 12:
                parseMechanicalSupplyRoom(curGame, curRoom, userInput);
                break;
            case 13:
                parseLiveRobotAnimals(curGame, curRoom, userInput);
                break;
            case 14:
                parseMockForest(curGame, curRoom, userInput);
                break;
            case 15:
                parseMonitoringRoom(curGame, curRoom, userInput);
        }
    }
}
