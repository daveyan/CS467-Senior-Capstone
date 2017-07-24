#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

using std::vector;
using std::string;

using std::cout;
using std::endl;

class Item {
private:
    int id;
    string name;
    string description;
    string itemPath;
    bool inInventory;
public:
    Item(int id, string name);//, string description);
    void setId(int id);
    void setName(string name);
    //void setDescription(string description);
    int getId();
    string getName();
    void getDescription(int inInv,string userCommand);
    bool getInInventory();
};

#endif
