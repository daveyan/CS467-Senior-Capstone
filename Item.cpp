#include "Item.hpp"
#include "ParseLine.hpp"

Item::Item(int id, string name, string description) {
	this->id = id;
	this->name = name;
	this->description = description;
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