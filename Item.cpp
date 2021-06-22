#include "stdafx.h"
#include "iostream"
#include "string"
#include "Item.h"

using namespace std;

Item::Item(string name, string description, Room* usageRoom, string message) : Entity(ITEM, name, description)
{
	this->name = name;
	this->description = description;
	this->searched = false;
	this->usageRoom = usageRoom;
	this->message = message;
}

Item::~Item()
{

}