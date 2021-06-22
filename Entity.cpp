#include "stdafx.h"
#include "iostream"
#include "string"
#include "Entity.h"

using namespace std;

Entity::Entity(EntityType type, string name, string description)
{
	list<Entity*> l;

	this->type = type;
	this->name = name;
	this->description = description;
	this->contains = l;
}

Entity::~Entity()
{

}

void Entity::Update()
{

}

void Entity::AddEntity(Entity* entity)
{
	contains.push_back(entity);
}

void Entity::RemoveEntity(Entity* entity)
{
	contains.remove(entity);
}