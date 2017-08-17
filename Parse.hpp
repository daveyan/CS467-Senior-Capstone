#ifndef PROJECT_PARSE_HPP
#define PROJECT_PARSE_HPP

#include "Game.hpp"

class Parse {
public:
    Parse();
    //void popActions();
    //void popEntranceItemNouns();

    vector<string> actions = {"pick", "pick up", "snag", "lift", "scoop", "grab", "inspect", "check", "read", "open", "take"};
    //vector<string> actions;
    vector<string> entranceItemNouns = {"bar", "metal bar", "pipe", "metal pipe"};
    vector<string> vestibuleFlashlightNouns = {"flashlight", "flash light"};
    vector<string> garageItemNouns = {"key card", "keycard"};
    vector<string> breakroomItemNouns = {"hat", "hard hat"};
    vector<string> officeItemNouns = {"file", "files"};
    vector<string> mockforestItemNouns = {"post", "postit", "post it"};
    vector<string> mechanicalsupplyItemNouns = {"net", "exploding net"};
    vector<string> monitoringroomItemNouns = {"opener"};
    //vector<string> entranceItemNouns;
    //vector<string> vestibuleFlashlightNouns;
    //vector<string> garageItemNouns;
    //vector<string> breakroomItemNouns;
    //vector<string> officeItemNouns;
    //vector<string> mockforestItemNouns;
    //vector<string> mechanicalsupplyItemNouns;
    //vector<string> monitoringroomItemNouns;
    Room* findRoom(Game &curGame, string name);
    bool checkForMatch(vector<string> collection1, vector<string> collection2, string userInput);
    void parseInput(Game &curGame, Room *curRoom, string userInput);
    void parseEntrance(Game &curGame, Room *curRoom, string userInput);
    void parseVestibule(Game &curGame, Room *curRoom, string userInput);
    void parseMechanicalRoom(Game &curGame, Room *curRoom, string userInput);
    void parseGarage(Game &curGame, Room *curRoom, string userInput);
    void parseLounge(Game &curGame, Room *curRoom, string userInput);
    void parseBreakRoom(Game &curGame, Room *curRoom, string userInput);
    void parseBathroom(Game &curGame, Room *curRoom, string userInput);
    void parseOffice(Game &curGame, Room *curRoom, string userInput);
    void parseComputerLab(Game &curGame, Room *curRoom, string userInput);
    void parseLiveRobotAnimals(Game &curGame, Room *curRoom, string userInput);
    void parseMockForest(Game &curGame, Room *curRoom, string userInput);
    void parseTaxidermy(Game &curGame, Room *curRoom, string userInput);
    void parseRobotAssemblyRoom(Game &curGame, Room *curRoom, string userInput);
    void parseMechanicalSupplyRoom(Game &curGame, Room *curRoom, string userInput);
    void parseMonitoringRoom(Game &curGame, Room *curRoom, string userInput);
};


#endif
