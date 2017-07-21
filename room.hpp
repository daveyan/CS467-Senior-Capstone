#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

using std::vector;
using std::string;

using std::cout;
using std::endl;

class Room {
private:
    int id;
    string name;
    vector<int> items;
    vector<int> itemsDropped;
    vector<int> adjRooms;
    string roomPath;    //for the reader, we don't need both Desc. Just a file path that is created in the constructor
    //string shortDesc;
    //string longDesc;
    bool visited;
public:
    Room(int id, string name);//, string shortDesc, string longDesc);
    void setId(int id);
    void setName(string name);
    void addAdjRoom(int roomId);
    //void setShortDesc(string desc);
    //void setLongDesc(string desc);
    void visitRoom();
    int getId();
    string getName();
    vector<int> getItems();
    vector<int> getDroppedItems();
    //string getDescription();
    void getDescription(int visit, string command); 
    bool isVisited();

};





#endif
