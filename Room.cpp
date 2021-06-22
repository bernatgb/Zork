#include "stdafx.h"
#include "iostream"
#include "string"
#include "Room.h"

using namespace std;

Room::Room(string name, string description) : Entity(ROOM, name, description)
{
	this->name = name;
	this->description = description;
}


Room::~Room()
{

}