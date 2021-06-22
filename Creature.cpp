#include "stdafx.h"
#include "iostream"
#include "string"
#include "Creature.h"

using namespace std;

Creature::Creature(string name, string description, Room* location) : Entity(CREATURE, name, description)
{
	this->name = name;
	this->description = description;
	this->location = location;
}

Creature::~Creature()
{

}