#include "Room.hpp"

Room::Room(int id, string name, string shortDesc, string longDesc) {
    this->id = id;
    this->name = name;
    this->shortDesc = shortDesc;
    this->longDesc = longDesc;
    this->visited = false;
}

void Room::setId(int id) {
    this->id = id;
}

void Room::setName(string name) {
    this->name = name;
}

void Room::addNorth(int roomId) {
    north = roomId;
}

void Room::addSouth(int roomId) {
    south = roomId;
}

void Room::addEast(int roomId) {
    east = roomId;
}

void Room::addWest(int roomId) {
    west = roomId;
}

void Room::setShortDesc(string desc) {
    this->shortDesc = desc;
}

void Room::setLongDesc(string desc) {
    this->longDesc = desc;
}

void Room::visitRoom() {
    this->visited = true;
}

void Room::addItem(Item item) {
    items.push_back(item);
}

int Room::getId() {
    return id;
}

int Room::getNorth() {
    return north;
}

int Room::getSouth() {
    return south;
}

int Room::getEast() {
    return east;
}

int Room::getWest() {
    return west;
}

string Room::getName() {
    return name;
}

vector<Item> Room::getItems() {
    return items;
}

vector<Item> Room::getDroppedItems() {
    return itemsDropped;
}

string Room::getDescription() {
    if (!visited) {
        visited = true;
        return longDesc;
    } else {
        return shortDesc;
    }
}

bool Room::isVisited() {
    return visited;
}