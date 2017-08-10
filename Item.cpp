#include "Item.hpp"
#include "ParseLine.hpp"

Item::Item(int id, string name, string description) {
	this->id = id;
	this->name = name;
	this->description = description;
	this->itemPath = "src/items/allitems.txt";
}

void Item::setId(int id) {
	this->id = id;
}

void Item::setName(string name) {
	this->name = name;
}

void Item::setDescription(string description) {
	this->description = description;
}

int Item::getId() {
	return id;
}

string Item::getName() {
	return name;
}

string Item::getDescription() {
	return description;
}

string Item::readDescription(string itemName){
	 bool linesWritten = false;

    //general command template [start|end + itemName]

    //[start|end
    string startCommand = "[start";
    string endCommand = "[end";
    string command;

    //long|short|Feature1|Feature2roomFile
    command.append(itemName);
    command.append("]");
    
    //appending start end commands 
    startCommand.append(command);
    endCommand.append(command);


    string readString;
    std::ifstream itemFile(itemPath.c_str());

    if(!itemFile.is_open()){
        cout << "Failed to open file" << endl;
        return "Error";
    }
    
    string allread = "";

    while(std::getline(itemFile,readString)){
        if(readString.find(startCommand) != string::npos){
            while(std::getline(itemFile,readString)){
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