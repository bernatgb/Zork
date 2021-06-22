#include "stdafx.h"
#include "iostream"
#include "string"
#include "Exit.h"

using namespace std;

Exit::Exit(ExitDirection direction, Room* source, Room* destination, bool locked, int code) : Entity(EXIT, "", "")
{
	this->direction = direction;
	this->source = source;
	this->destination = destination;
	this->locked = locked;
	this->code = code;
}

Exit::~Exit()
{

}

string Exit::DirectionName(ExitDirection ed)
{
	switch (ed)
	{
	case NORTH:
		return "north";
	case SOUTH:
		return "south";
	case WEST:
		return "west";
	case EAST:
		return "east";
	default:
		return "";
	}
}

int Exit::DirectionNumber(string dir)
{
	if (dir[0] == 'n' || dir[0] == 'N')
	{
		return 0;
	}
	else if (dir[0] == 's' || dir[0] == 'S')
	{
		return 1;
	}
	else if (dir[0] == 'w' || dir[0] == 'W')
	{
		return 2;
	}
	else if (dir[0] == 'e' || dir[0] == 'E')
	{
		return 3;
	}
	else
		return 4;
}