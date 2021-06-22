#pragma once
#include "iostream"
#include "Entity.h"

class Room; 

using namespace std;

class Item : public Entity
{
public:
	Item(string name, string description, Room* usageRoom, string message);
	~Item();

	string name;
	string description;
	bool searched;
	Room* usageRoom;
	string message;
};