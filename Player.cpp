#include "stdafx.h"
#include "iostream"
#include "string"
#include "Player.h"

using namespace std;

Player::Player(string name, string description, Room* location, list<Entity*> worldEntities) : Creature(name, description, location)
{
	this->name = name;
	this->description = description;
	this->location = location;
	this->worldEntities = worldEntities;
	this->lockerUnlock = false;
	this->car = false;
	this->prisoner = false;
	this->killer = false;
}

Player::~Player()
{

}

void Player::Help()
{
	cout << "You are " << name << description << endl;
	cout << "To take a look at the room, press L." << endl;
	cout << "To go to a different room, press G." << endl;
	cout << "To search items, press S." << endl;
	cout << "To pick an item, press P." << endl;
	cout << "To drop an item, press D." << endl;
	cout << "To use a picked item, press U." << endl;
	cout << "To open a locked door, press O." << endl;
	if (location->name == "the nursing room.")
		cout << "To talk to otherone, press T." << endl;
	if (location->name == "the parking." && car)
		cout << "To escape, press E." << endl;
	cout << "To surrender en finish your try to escape, press F." << endl << endl;
}

void Player::Look()
{
	cout << "Now you are in " << location->name << endl;
	cout << location->description << endl << endl;
}

void Player::Go()
{
	vector<bool> possible(4);
	vector<Exit*> exits(4);
	cout << "From here, you can go to:" << endl;
	Exit* exit = new Exit(NORTH, NULL, NULL, NULL, NULL);

	for (list<Entity*>::iterator it = worldEntities.begin(); it != worldEntities.end(); ++it)
	{
		if ((*it)->type == EXIT)
		{
			exit = (Exit*)*it;
			if (exit->source->name == location->name)
			{
				cout << "From " << exit->source->name << " on the " << exit->DirectionName(exit->direction) << " you have the " << exit->destination->name << "." << endl;
				possible[exit->direction] = true;
				exits[exit->direction] = exit;
			}

		}
	}

	cout << endl << "Where do you want to go? (N/S/E/W)" << endl;
	string dir;
	cin >> dir;
	cout << endl;
	int dirNum = exit->DirectionNumber(dir);

	if (dirNum == 4)
	{
		cout << "Sorry, this direction doesn't exist." << endl << endl;;
	}
	else
	{
		if (possible[dirNum])
		{
			if (exits[dirNum]->locked == true)
				cout << "Sorry, for the moment, this door is locked." << endl << endl;
			else
			{
				location = exits[dirNum]->destination;
				cout << "Now, you are in " << location->name << endl << endl;
			}
		}
		else
			cout << "Sorry, you can't go in this direction." << endl << endl;
	}

}

void Player::Search()
{
	cout << "Here there are the next items:" << endl;
	bool items = false;

	for (list<Entity*>::iterator it = location->contains.begin(); it != location->contains.end(); ++it)
	{
		if ((*it)->type == ITEM)
		{
			Item* item = (Item*)*it;

			// If only to hide the items of the locker.
			if (item->name == "A gun." || item->name == "Hunter's photo.")
			{
				if (!lockerUnlock)
					break;
			}

			items = true;
			cout << item->name << " " << item->description << endl;
			item->searched = true;
		}
	}

	if (!items)
	{
		cout << "There are no items." << endl;
	}

	cout << endl;
}

void Player::Pick()
{
	cout << "Here you can pick the next items:" << endl;
	int itemsCount = 0;
	vector<Item*> items;

	for (list<Entity*>::iterator it = location->contains.begin(); it != location->contains.end(); ++it)
	{
		if ((*it)->type == ITEM)
		{
			Item* item = (Item*)*it;
			if (item->searched)
			{
				++itemsCount;
				cout << itemsCount << ".- " << item->name << " " << item->description << endl;
				items.push_back(item);
			}
		}
	}

	if (itemsCount == 0)
	{
		cout << "There are no items to pick." << endl << endl;
	}
	else
	{
		cout << endl << "Which item do you want to pick? Enter the corresponding number." << endl;
		size_t picking;
		cin >> picking;
		cout << endl;

		if (picking > items.size())
		{
			cout << "Sorry, this number doesn't correspond to any item." << endl << endl;
		}
		else
		{
			location->RemoveEntity(items[picking - 1]);
			cout << "You've picked " << items[picking - 1]->name << endl << endl;
			bag.push_back(items[picking - 1]);
		}
	}
}

void Player::Drop()
{
	if (bag.empty())
		cout << "You don't have any item to drop." << endl << endl;
	else
	{
		cout << "You have the next items to drop:" << endl;
		int itemsCount = 0;
		vector<Item*> items;

		for (list<Item*>::iterator it = bag.begin(); it != bag.end(); ++it)
		{
			Item* item = (Item*)*it;
			++itemsCount;
			cout << itemsCount << ".- " << item->name << " " << item->description << endl;
			items.push_back(item);
		}

		cout << endl << "Which item do you want to drop? Enter the corresponding number." << endl;
		size_t drop;
		cin >> drop;
		cout << endl;

		if (drop > bag.size())
			cout << "Sorry, this number doesn't correspond to any item." << endl << endl;
		else
		{
			bag.remove(items[drop - 1]);
			location->AddEntity(items[drop - 1]);
		}
	}
}

void Player::Use()
{
	if (bag.empty())
		cout << "You don't have any item to use." << endl << endl;
	else
	{
		cout << "You have the next items to use:" << endl;
		int itemsCount = 0;
		vector<Item*> items;

		for (list<Item*>::iterator it = bag.begin(); it != bag.end(); ++it)
		{
			Item* item = (Item*)*it;
			++itemsCount;
			cout << itemsCount << ".- " << item->name << " " << item->description << endl;
			items.push_back(item);
		}

		cout << endl << "Which item do you want to use? Enter the corresponding number." << endl;
		size_t use;
		cin >> use;
		cout << endl;

		if (use > bag.size())
			cout << "Sorry, this number doesn't correspond to any item." << endl << endl;
		else
		{
			if (location == items[use - 1]->usageRoom)
			{
				if (items[use - 1]->name == "Key with the number 1.")
				{
					lockerUnlock = true;
					// Now the items of the locker aren't hidden for the search function.
				}
				else if (items[use - 1]->name == "Car key.")
				{
					car = true;
					// Now you have access to the car.
				}
				else if (items[use - 1]->name == "A gun.")
				{
					killer = true;
				}
				cout << items[use - 1]->message << endl;
			}
			else
				cout << "Sorry, there is no use for this item here." << endl << endl;
		}
	}
}

void Player::Open()
{
	vector<bool> possible(4);
	vector<Exit*> exits(4);
	int exitsCount = 0;
	Exit* exit = new Exit(NORTH, NULL, NULL, NULL, NULL);

	for (list<Entity*>::iterator it = worldEntities.begin(); it != worldEntities.end(); ++it)
	{
		if ((*it)->type == EXIT)
		{
			exit = (Exit*)*it;
			if (exit->source->name == location->name && exit->locked == true)
			{
				cout << "From " << exit->source->name << " on the " << exit->DirectionName(exit->direction) << " you have the door going to " << exit->destination->name << " locked." << endl;
				possible[exit->direction] = true;
				exits[exit->direction] = exit;
				++exitsCount;
			}
		}
	}

	if (exitsCount == 0)
		cout << "Sorry, there are no doors left to be unlocked in this room." << endl << endl;
	else
	{
		cout << "Which door do you want to open? (N/S/E/W)" << endl;
		string dir;
		cin >> dir;
		cout << endl;
		int dirNum = exit->DirectionNumber(dir);

		if (dirNum == 4)
		{
			cout << "Sorry, this direction doesn't exist." << endl << endl;;
		}
		else
		{
			if (possible[dirNum])
			{
				cout << "Enter the code to unlock the door." << endl;
				int codeEntered;
				cin >> codeEntered;
				cout << endl;
				if (exits[dirNum]->code == codeEntered)
				{
					exits[dirNum]->locked = false;
					cout << "Now this door is unlocked." << endl << endl;
				}
				else
					cout << "Wrong code." << endl << endl;
			}
			else
				cout << "Sorry, there are no doors to unlock in this direction." << endl << endl;
		}
	}
}

void Player::Talk()
{
	string answer;
	bool answered1 = false;
	cout << "Hey you, help me! I made a plan but the asshole of the parking's guard beat me up and now I'm here. Do you want me to help you? (Y/N)" << endl;
	cin >> answer;
	cout << endl;

	while (!answered1)
	{
		if (answer[0] == 'Y' || answer[0] == 'y')
		{
			answered1 = true;
			cout << "Okay, listen carefully. There is the ventilation pipe. The nurse uses it to bring her boyfriend from outside.";
			cout << "He cames at 12 o'clock at night and leaves at 6 in the morning. I assume it is when the guards change their turn.";
			cout << "I don't where the pipe goes but I've seen part of the code of the padlock that keeps the gate closed.";
			cout << "The first number is a 0 and the second is a 6, I don't know the third one.";
			cout << "We could try to escape at 6, but I need yoor help to walk. Are you gonna help me? (Y/N)" << endl;

			cin >> answer;
			cout << endl;
			bool answered2 = false;

			while (!answered2)
			{
				if (answer[0] == 'Y' || answer[0] == 'y')
				{
					answered2 = true;
					prisoner = true;
					cout << "Okey, c'mon, let's go." << endl << endl;

				}
				else if (answer[0] == 'N' || answer[0] == 'n')
				{
					answered2 = true;
					cout << "Fuck you, I wish you don't achieve it!" << endl;
				}
				else
				{
					cout << "What? Are you gonna help me or not, we don't have much time? (Y/N)" << endl;
					cin >> answer;
					cout << endl;
				}
			}

		}
		else if (answer[0] == 'N' || answer[0] == 'n')
		{
			answered1 = true;
			cout << "I don't need you neither anyway." << endl;
		}
		else
		{
			cout << "What? Do you want me to help you or not? (Y/N)" << endl;
			cin >> answer;
			cout << endl;
		}
	}
}

void Player::Escape()
{
	// Final 1
	if (!killer && !prisoner)
	{
		cout << "You've waited for the guards' turn change. You runned to the car, entered and escaped with it. You left behind someone who helped you but... Congratulations, now you are free." << endl;
	}

	// Final 2
	if (killer && !prisoner)
	{
		cout << "You've entered as an innocent and you leave as a guilty person. But... Congratulations, now you are free." << endl;
	}

	// Final 3
	if (killer && prisoner)
	{
		cout << "You've saved a person and gained a friend for ever and murdered another one. But... Congratulations, now you are free." << endl;
	}

	// Final 4
	if (!killer && prisoner)
	{
		cout << "You were too slow to run to the car without being seen. The guard shooted, and killed you. You died but at least you remained innocent until the end." << endl;
	}

	cout << "Thanks for playing! Play again to see the other finals." << endl;
	escaped = true;
}