#pragma once
#include "iostream"
#include "Entity.h"

class Room;

using namespace std;

class Creature : public Entity
{
public:
	Creature(string name, string description, Room* location);
	~Creature();

	string name;
	string description;
	Room* location;
};
