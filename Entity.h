#pragma once
#include "iostream"
#include "list"

using namespace std;

enum EntityType
{
	ENTITY,
	CREATURE,
	EXIT,
	ROOM,
	ITEM
};

class Entity
{
public:
	Entity(EntityType type, string name, string description);
	virtual ~Entity();

	EntityType type;
	string name;
	string description;
	list<Entity*> contains;

	void Update();
	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);
};