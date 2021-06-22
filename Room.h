#pragma once
#include "stdafx.h"
#include "iostream"
#include "string"
#include "Entity.h"

using namespace std;

class Room : public Entity
{
public: 
	Room(string name, string description);
	~Room();

	string name;
	string description;
};