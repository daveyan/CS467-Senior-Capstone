#include "Item.hpp"

Item::Item(int id, string name){ //, string description) {
    this->id = id;
    this->name = name;
    //this->description = description;
    this->itemPath = "src/items/"+ name + ".txt";
    this->itemPath.erase(remove_if(itemPath.begin(),itemPath.end(),::isspace),itemPath.end());
    this->inInventory = false;
}

void Item::setId(int id) {
    this->id = id;
}

void Item::setName(string name) {
    this->name = name;
}

/*
void Item::setDescription(string description) {
    this->description = description;
}
*/


int Item::getId() {
    return id;
}

string Item::getName() {
    return name;
}

 void Item::getDescription(int inInv ,string userCommand){
    bool linesWritten = false;

    //general command template [start|end + user command + item name + yes|no]

    //[start|end
    string startCommand = "[start";
    string endCommand = "[end";
    string command;

    // + item name
    string trimmedItemName = name;
    trimmedItemName.erase(remove_if(trimmedItemName.begin(),trimmedItemName.end(), ::isspace), trimmedItemName.end());
    // + user command
    command.append(userCommand);
    command.append(trimmedItemName);

    // + yes|no]
    if(inInv){
        command.append("yes]");
    }
    else{
        command.append("no]");
    }

    //appending to the start end commands
    startCommand.append(command);
    endCommand.append(command);


    string readString;
    std::ifstream itemFile(itemPath.c_str());

    if(!itemFile.is_open()){
        cout << "Failed to open file" << endl;
    }
    
    while(std::getline(itemFile,readString)){
        if(readString.find(startCommand) != string::npos){
            while(std::getline(itemFile,readString)){
                if(readString.find(endCommand) != string::npos){
                    break;
                }
                else{
                cout << readString << endl;
                linesWritten = true;
                }                       
            }
            
        }
    }

    if(!linesWritten){
        cout << "Failed to find starting point" << endl;
    }


}

bool Item::getInInventory() {
    return inInventory;
}
