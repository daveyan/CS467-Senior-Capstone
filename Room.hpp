#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>

#include "Item.hpp"

using std::vector;
using std::string;

class Room {
private:
    int id;
    string name;
    int north;
    int south;
    int east;
    int west;
    string northExitStatus = "";
    string southExitStatus = "";
    string eastExitStatus = "";
    string westExitStatus = "";
    string shortDesc;
    string longDesc;
    string feature1Response;
    string feature2Response;
    string feature1Key;
    string feature2Key;

    vector<string> itemsDropped;
    bool visited;
public:

    bool hasItem = false;
    bool hasSecondItem = false;

    string item;
    Room();
    Room(int id, string name, string shortDesc, string longDesc);
    void setId(int id);
    void setName(string name);
    void addNorth(int roomId);
    void addSouth(int roomId);
    void addEast(int roomId);
    void addWest(int roomId);
    void setNorthExitStatus(string status);
    void setSouthExitStatus(string status);
    void setEastExitStatus(string status);
    void setWestExitStatus(string status);
    void setShortDesc(string desc);
    void setLongDesc(string desc);
    void setFeature1Response(string resp);
    void setFeature2Response(string resp);
    void setFeature1Key(string key);
    void setFeature2Key(string key);
    void visitRoom();
    void addStartingItem(string item);
    void addItem(string item);
    void removeItem(string item);
    int getId();
    int getNorth();
    int getSouth();
    int getEast();
    int getWest();
    string getNorthExitStatus();
    string getSouthExitStatus();
    string getEastExitStatus();
    string getWestExitStatus();
    string getName();
    string getItem();
    vector<string> getDroppedItems();
    string getDescription();
    string getShortDesc();
    string getLongDesc();
    string getFeature1Response();
    string getFeature2Response();
    string getFeature1Key();
    string getFeature2Key();
    bool isVisited();
};





#endif
