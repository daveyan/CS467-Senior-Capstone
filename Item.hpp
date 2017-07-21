#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

using std::string;

class Item {
private:
    int id;
    string name;
    string description;
public:
    Item(int id, string name, string description);
    void setId(int id);
    void setName(string name);
    void setDescription(string description);
    int getId();
    string getName();
    string getDescription();
};

#endif
