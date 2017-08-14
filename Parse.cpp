#include <iostream>
#include <string>
#include <string.h>
#include "Parse.hpp"

using std::cout;
using std::endl;

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

void Parse::parseEntrance(Game &curGame, Room *curRoom, string userInput) {
    // If the user wants to go north
    if (strstr(userInput.c_str(), "go north") != NULL) {
        if (!curGame.inInventory("bar")) {
            cout << "You should have a bar to pry the door open..." << endl;
        } else {
            cout << "The door is now to open to go through since you pried it open with the metal bar" << endl;
            curGame.curRoom = curRoom->getNorth();
        }
    // If the user wants to go south
    } else if (strstr(userInput.c_str(), "go south") != NULL) {
        cout << "There is nowhere south of here" << endl;
    // If the user wants to go east
    } else if (strstr(userInput.c_str(), "go east") != NULL) {
        cout << "There is nowhere east of here" << endl;
    // If the user wants to go west
    } else if (strstr(userInput.c_str(), "go west") != NULL) {
        cout << "There is nowhere west of here" << endl;
    // Check if the user wants to pick up the bar
    } else if (checkForMatch(actions, entranceItemNouns, userInput)) {
        // user wants to grab bar
        // Check if already in inventory
        if (curGame.inInventory("bar")) {
            cout << "You already have that in your inventory." << endl;
        } else {        
            curGame.addToInventory("bar");
            curRoom->item = "null";
            cout << "You have grabbed the metal bar." << endl;
        }
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseVestibule(Game &curGame, Room *curRoom, string userInput) {
    // If the user wants to go north
    if (strstr(userInput.c_str(), "go north") != NULL) {
        // Need keycard
        if (!curGame.inInventory("keycard")) {
            cout << "You need a keycard to go through the door open..." << endl;
        } else {
            curGame.curRoom = curRoom->getNorth();
        }

    } else if (strstr(userInput.c_str(), "go south") != NULL) {
        curGame.curRoom = curRoom->getSouth();

    } else if (strstr(userInput.c_str(), "go east") != NULL) {
        // Need flashlight
        if (!curGame.inInventory("flashlight")) {
            cout << "You should have a flashlight before going into such a dark room..." << endl;
        } else {
            cout << "You have the illumination necessary to go east" << endl;
            curGame.curRoom = curRoom->getEast();
        }

    } else if (strstr(userInput.c_str(), "go west") != NULL) {
        cout << "There is nowhere west of here" << endl;

    } else if (checkForMatch(actions, vestibuleFlashlightNouns, userInput)) {
        if (curGame.inInventory("flashlight")) {
            cout << "You already have that in your inventory." << endl;
        } else {        
            curGame.addToInventory("flashlight");
            curRoom->item = "null";
            cout << "You have grabbed the flashlight." << endl;
        }
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseMechanicalRoom(Game &curGame, Room *curRoom, string userInput) {
    if (strstr(userInput.c_str(), "go north") != NULL) {
        cout << "There is nowhere north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL) {
        cout << "There is nowhere south of here" << endl;
    } else if (strstr(userInput.c_str(), "go east") != NULL) {
        curGame.curRoom = curRoom->getEast();
    } else if (strstr(userInput.c_str(), "go west") != NULL) {
        curGame.curRoom = curRoom->getWest();
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseGarage(Game &curGame, Room *curRoom, string userInput) {
    if (strstr(userInput.c_str(), "go north") != NULL) {
        cout << "There is nowhere north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL) {
        cout << "There is nowhere south of here" << endl;
    } else if (strstr(userInput.c_str(), "go east") != NULL) {
        if (!curGame.inInventory("opener")) {
            cout << "Looks like a garage door opener is needed to leave this way..." << endl;
        } else {
            cout << "You should have opened the garage door, sped out, and now you are free to tell the world about what you learned!" << endl;
            curGame.isFinished = true;
        }
    } else if (strstr(userInput.c_str(), "go west") != NULL) {
        curGame.curRoom = curRoom->getWest();
    } else if (checkForMatch(actions, garageItemNouns, userInput)) {
        // user wants to grab keycard
        if (curGame.inInventory("keycard")) {
            cout << "You already have that in your inventory." << endl;
        } else {        
            curGame.addToInventory("keycard");
            curRoom->item = "null";
            cout << "You have grabbed the keycard." << endl;
        }
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseBreakRoom(Game &curGame, Room *curRoom, string userInput) {
    if (strstr(userInput.c_str(), "go north") != NULL) {
        cout << "There is nowhere north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL) {
        cout << "There is nowhere south of here" << endl;
    } else if (strstr(userInput.c_str(), "go east") != NULL) {
        curGame.curRoom = curRoom->getEast();
    } else if (strstr(userInput.c_str(), "go west") != NULL) {
        curGame.curRoom = curRoom->getWest();
    } else if (checkForMatch(actions, breakroomItemNouns, userInput)) {
        // user wants to grab hat
        if (curGame.inInventory("hat")) {
            cout << "You already have that in your inventory." << endl;
        } else {        
            curGame.addToInventory("hat");
            curRoom->item = "null";
            cout << "You have grabbed the hard hat." << endl;
        }
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseBathroom(Game &curGame, Room *curRoom, string userInput) {
    if (strstr(userInput.c_str(), "go north") != NULL) {
        cout << "There is nowhere north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL) {
        cout << "There is nowhere south of here" << endl;
    } else if (strstr(userInput.c_str(), "go east") != NULL) {
        curGame.curRoom = curRoom->getEast();
    } else if (strstr(userInput.c_str(), "go west") != NULL) {
        cout << "There is nowhere west of here" << endl;
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseLounge(Game &curGame, Room *curRoom, string userInput) {
    if (strstr(userInput.c_str(), "go north") != NULL) {
        curGame.curRoom = curRoom->getNorth();
    } else if (strstr(userInput.c_str(), "go south") != NULL) {
        curGame.curRoom = curRoom->getSouth();
    } else if (strstr(userInput.c_str(), "go east") != NULL) {
        curGame.curRoom = curRoom->getEast();
    } else if (strstr(userInput.c_str(), "go west") != NULL) {
        curGame.curRoom = curRoom->getWest();
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseOffice(Game &curGame, Room *curRoom, string userInput) {
    if (strstr(userInput.c_str(), "go north") != NULL) {
        cout << "There is nowhere north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL) {
        cout << "There is nowhere south of here" << endl;
    } else if (strstr(userInput.c_str(), "go east") != NULL) {
        cout << "There is nowhere east of here" << endl;
    } else if (strstr(userInput.c_str(), "go west") != NULL) {
        curGame.curRoom = curRoom->getWest();
    } else if (checkForMatch(actions, officeItemNouns, userInput)) {
        // user wants to grab file
        if (curGame.inInventory("file")) {
            cout << "You already have that in your inventory." << endl;
        } else {        
            curGame.addToInventory("file");
            curRoom->item = "null";
            cout << "You have grabbed the file." << endl;
        }
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseComputerLab(Game &curGame, Room *curRoom, string userInput) {
    if (strstr(userInput.c_str(), "go north") != NULL) {
        // Need postit
        if (!curGame.inInventory("postit")) {
            cout << "You need the passcode to open the door. Maybe it is written down somewhere..." << endl;
        } else {
            cout << "You use the passcode to go through the door" << endl;
            curGame.curRoom = curRoom->getNorth();
        }
    } else if (strstr(userInput.c_str(), "go south") != NULL) {
        curGame.curRoom = curRoom->getSouth();
    } else if (strstr(userInput.c_str(), "go east") != NULL) {
        // Need hard had
        if (!curGame.inInventory("hat")) {
            cout << "It sounds dangerous in there. Maybe you should have some protective equipment..." << endl;
        } else {
            cout << "With the hard hat on, you move forward..." << endl;
            curGame.curRoom = curRoom->getEast();
        }
    } else if (strstr(userInput.c_str(), "go west") != NULL) {
        curGame.curRoom = curRoom->getWest();
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseLiveRobotAnimals(Game &curGame, Room *curRoom, string userInput) {
    if (strstr(userInput.c_str(), "go north") != NULL) {
        cout << "There is nowhere north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL) {
        cout << "There is nowhere south of here" << endl;
    } else if (strstr(userInput.c_str(), "go east") != NULL) {
        // Need net
        if (!curGame.inInventory("net")) {
            cout << "Something should be used to secure the area before moving forward..." << endl;
        } else {
            cout << "The net was thrown, capturing the owl, allowing you to move forward" << endl;
            curGame.curRoom = curRoom->getEast();
        }
    } else if (strstr(userInput.c_str(), "go west") != NULL) {
        curGame.curRoom = curRoom->getWest();
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseMockForest(Game &curGame, Room *curRoom, string userInput) {
    if (strstr(userInput.c_str(), "go north") != NULL) {
        cout << "There is nowhere to the north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL) {
        cout << "There is nowhere to the south of here" << endl;
    } else if (strstr(userInput.c_str(), "go east") != NULL) {
        cout << "There is nowhere to the east of here" << endl;
    } else if (strstr(userInput.c_str(), "go west") != NULL) {
        curGame.curRoom = curRoom->getWest();
    } else if (checkForMatch(actions, mockforestItemNouns, userInput)) {
        // user wants to grab file
        if (curGame.inInventory("postit")) {
            cout << "You already have that in your inventory." << endl;
        } else {        
            curGame.addToInventory("postit");
            curRoom->item = "null";
            cout << "You have grabbed the postit." << endl;
        }
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseTaxidermy(Game &curGame, Room *curRoom, string userInput) {
    if (strstr(userInput.c_str(), "go north") != NULL) {
        cout << "There is nowhere north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL) {
        cout << "There is nowhere south of here" << endl;
    } else if (strstr(userInput.c_str(), "go east") != NULL) {
        curGame.curRoom = curRoom->getEast();
    } else if (strstr(userInput.c_str(), "go west") != NULL) {
        curGame.curRoom = curRoom->getWest();
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseRobotAssemblyRoom(Game &curGame, Room *curRoom, string userInput) {
    if (strstr(userInput.c_str(), "go north") != NULL) {
        cout << "There is nowhere north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL) {
        cout << "There is nowhere south of here" << endl;
    } else if (strstr(userInput.c_str(), "go east") != NULL) {
        curGame.curRoom = curRoom->getEast();
    } else if (strstr(userInput.c_str(), "go west") != NULL) {
        curGame.curRoom = curRoom->getWest();
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseMechanicalSupplyRoom(Game &curGame, Room *curRoom, string userInput) {
    if (strstr(userInput.c_str(), "go north") != NULL) {
        cout << "There is nowhere north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL) {
        cout << "There is nowhere south of here" << endl;
    } else if (strstr(userInput.c_str(), "go east") != NULL) {
        curGame.curRoom = curRoom->getEast();
    } else if (strstr(userInput.c_str(), "go west") != NULL) {
        cout << "There is nowhere west of here" << endl;
    } else if (checkForMatch(actions, mechanicalsupplyItemNouns, userInput)) {
        // user wants to grab net
        if (curGame.inInventory("net")) {
            cout << "You already have that in your inventory." << endl;
        } else {        
            curGame.addToInventory("net");
            curRoom->item = "null";
            cout << "You have grabbed the exploding net." << endl;
        }
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseMonitoringRoom(Game &curGame, Room *curRoom, string userInput) {
    if (strstr(userInput.c_str(), "go north") != NULL) {
        cout << "There is nowhere north of here" << endl;
    } else if (strstr(userInput.c_str(), "go south") != NULL) {
        curGame.curRoom = curRoom->getSouth();
    } else if (strstr(userInput.c_str(), "go east") != NULL) {
        cout << "There is nowhere east of here" << endl;
    } else if (strstr(userInput.c_str(), "go west") != NULL) {
        cout << "There is nowhere west of here" << endl;
    } else if (checkForMatch(actions, monitoringroomItemNouns, userInput)) {
        // user wants to grab opener
        if (curGame.inInventory("opener")) {
            cout << "You already have that in your inventory." << endl;
        } else {        
            curGame.addToInventory("opener");
            curRoom->item = "null";
            cout << "You have grabbed the garage door opener." << endl;
        }
    } else {
        cout << "Command not recognized" << endl;
    }
}

void Parse::parseInput(Game &curGame, Room *curRoom, string userInput) {

    // Check inventory
    if (strstr(userInput.c_str(), "inventory")) {
        cout << "Your inventory: " << endl;
        int invSize = curGame.inventory.size();
        for (int i = 0; i < invSize; i++) {
            cout << curGame.inventory[i] << endl;
        }

    // Feature 1 interaction
    } else if (strstr(userInput.c_str(), curRoom->getFeature1Key().c_str()) != NULL) {
        cout << curRoom->getFeature1Response() << endl;

    // Feature 2 interaction
    } else if (strstr(userInput.c_str(), curRoom->getFeature2Key().c_str()) != NULL) {
        cout << curRoom->getFeature2Response() << endl;

    // User wants to exit
    } else if (strstr(userInput.c_str(), "exit") != NULL) {
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
