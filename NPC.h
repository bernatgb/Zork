#pragma once
#include "iostream"
#include "Creature.h"

using namespace std;

class NPC : public Creature
{
public:
	NPC(string name, string description, Room* location);
	~NPC();

	string name;
	string description;
	Room* location;
};