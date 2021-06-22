#pragma once
#include "iostream"
#include "Creature.h"
#include "Exit.h"
#include "Room.h"
#include "Item.h"
#include "World.h"

using namespace std;

class Player : public Creature
{
public:
	Player(string name, string description, Room* location, list<Entity*> wordlEntities);
	~Player();

	string name;
	string description;
	Room* location;
	list<Item*> bag;
	list<Entity*> worldEntities;
	bool lockerUnlock;
	bool car;
	bool prisioner;
	bool killer;
	bool escaped;

	void Help();
	void Look();
	void Go();
	void Search();
	void Pick();
	void Drop();
	void Use();
	void Open();
	void Talk();
	void Escape();
};