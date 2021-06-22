#include "stdafx.h"
#include "iostream"
#include "string"
#include "NPC.h"

using namespace std;

NPC::NPC(string name, string description, Room* location) : Creature(name, description, location)
{
	this->name = name;
	this->description = description;
	this->location = location;
}

NPC::~NPC()
{

}