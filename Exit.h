#pragma once
#include "iostream"
#include "Entity.h"

class Room;
class Item;

using namespace std;

enum ExitDirection
{
	NORTH,
	SOUTH,
	WEST,
	EAST
};

class Exit : public Entity
{
public:
	Exit(ExitDirection direction, Room* source, Room* destination, bool locked, int code);
	~Exit();

	ExitDirection direction;
	Room* source;
	Room* destination;
	bool locked;
	int code;

	string DirectionName(ExitDirection);
	int DirectionNumber(string);
};