#include "Room.hpp"
#include <algorithm>

Room::Room(int id, string name, string shortDesc, string longDesc) {
    this->id = id;
    this->name = name;
    this->shortDesc = shortDesc;
    this->longDesc = longDesc;
    this->visited = false;
}

Room::Room() {
    id = -1;
    name = " ";
    shortDesc =  " ";
    longDesc = " ";
    visited = false;
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

void Room::setNorthExitStatus(string status) {
    northExitStatus = status;
}

void Room::setSouthExitStatus(string status) {
    southExitStatus = status;
}

void Room::setEastExitStatus(string status) {
    eastExitStatus = status;
}

void Room::setWestExitStatus(string status) {
    westExitStatus = status;
}

void Room::setShortDesc(string desc) {
    this->shortDesc = desc;
}

void Room::setLongDesc(string desc) {
    this->longDesc = desc;
}

void Room::setFeature1Response(string resp) {
    feature1Response = resp;
}

void Room::setFeature2Response(string resp) {
    feature2Response = resp;
}

void Room::setFeature1Key(string key) {
    feature1Key = key;
}

void Room::setFeature2Key(string key) {
    feature2Key = key;
}

void Room::visitRoom() {
    this->visited = true;
}

void Room::addItem(string item) {
    itemsDropped.push_back(item);
}

void Room::removeItem(string item) {
    itemsDropped.erase(std::remove(itemsDropped.begin(), itemsDropped.end(), item), itemsDropped.end());
}

void Room::addStartingItem(string item) {
    this->item = item;
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

string Room::getNorthExitStatus() {
    return northExitStatus;
}

string Room::getSouthExitStatus() {
    return southExitStatus;
}

string Room::getEastExitStatus() {
    return eastExitStatus;
}

string Room::getWestExitStatus() {
    return westExitStatus;
}

string Room::getName() {
    return name;
}

string Room::getItem() {
    return item;
}

vector<string> Room::getDroppedItems() {
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

string Room::getFeature1Response() {
    return feature1Response;
}

string Room::getFeature2Response() {
    return feature2Response;
}

string Room::getFeature1Key() {
    return feature1Key;
}

string Room::getFeature2Key() {
    return feature2Key;
}

string Room::getShortDesc() {
    return shortDesc;
}

string Room::getLongDesc() {
    return longDesc;
}

bool Room::isVisited() {
    return visited;
}