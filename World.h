#pragma once
#include "iostream"
#include "string"
#include "vector"
#include "Entity.h"
#include "Room.h"
#include "Exit.h"
#include "Item.h"
#include "Creature.h"
#include "NPC.h"
#include "Player.h"

using namespace std;

class Entity;

class World
{
public:
	World();
	~World();

	list<Entity*> entities;
	Room* currentLocation;
};