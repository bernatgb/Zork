#include "stdafx.h"
#include "iostream"
#include "string"
#include "vector"
#include "World.h"

using namespace std;

World::World()
{
	// Rooms
	Room* cell = new Room("the cell.", "Is where you are locked. There is a bed and a locked little wardrobe with next numbers written above it: 8021996");
	entities.push_back(cell);

	Room* corridor = new Room("the corridor.", "Is the main corridor for jail workers, there are three doors and the other side of the little wardrobe you crossed.");
	entities.push_back(corridor); 
	
	Room* lockers = new Room("the locker room.", "This is the locker room. There are the lockers of the security guards and a bench.");
	entities.push_back(lockers); 
	
	Room* directors = new Room("the Director's office.", "This is the director's office. There is a desk with a computer and a shelf with books.");
	entities.push_back(directors); 
	
	Room* nursing = new Room("the nursing room.", "This is the nursing room, there is another prisoner in bed.");
	entities.push_back(nursing); 

	Room* ventilation = new Room("the ventilation pipe.", "The ventilation pipe is dark, you hardly see light at the other side");
	entities.push_back(ventilation); 
	
	Room* parking = new Room("the parking.", "In the parking there are four simple cars and a luxury one. There is only a guard watching the parking.");
	entities.push_back(parking);



	// Exits
	Exit* cellExitNorth = new Exit(NORTH, cell, corridor, true, 8296);
	entities.push_back(cellExitNorth);

	Exit* corridorExitNorth = new Exit(NORTH, corridor, nursing, true, 1410);
	entities.push_back(corridorExitNorth);

	Exit* corridorExitSouth = new Exit(SOUTH, corridor, cell, false, 0);
	entities.push_back(corridorExitSouth);

	Exit* corridorExitWest = new Exit(WEST, corridor, directors, true, 155);
	entities.push_back(corridorExitWest);

	Exit* corridorExitEast = new Exit(EAST, corridor, lockers, false, 0);
	entities.push_back(corridorExitEast);

	Exit* lockersExitWest = new Exit(WEST, lockers, corridor, false, 0);
	entities.push_back(lockersExitWest);

	Exit* directorsExitEast = new Exit(EAST, directors, corridor, false, 0);
	entities.push_back(directorsExitEast);

	Exit* nursingExitSouth = new Exit(SOUTH, nursing, corridor, false, 0);
	entities.push_back(nursingExitSouth);

	Exit* nursingExitWest = new Exit(WEST, nursing, ventilation, true, 69);
	entities.push_back(nursingExitWest);

	Exit* ventilationExitWest = new Exit(WEST, ventilation, parking, false, 0);
	entities.push_back(ventilationExitWest);

	Exit* ventilationExitEast = new Exit(EAST, ventilation, nursing, false, 0);
	entities.push_back(ventilationExitEast);

	Exit* parkingExitEast = new Exit(EAST, parking, ventilation, false, 0);
	entities.push_back(parkingExitEast);



	// Items
	Item* letter = new Item("A letter from the previous prisoner of the cell.", "Letter with 4 holes from the previous prisoner of the cell. The letter says: My ticket to freedom! This guard is gonna pay.", cell, "If you put the letter where the numbers are, now you can't see the numbers 0, 1 and the first 9, but you can see the others through the holes");
	entities.push_back(letter);
	cell->AddEntity(letter);

	Item* lockerKey = new Item("Key 1.", "A key with the number 1 on a label.", lockers, "You have opened the locker number 1. Inside there is the a photo and a gun.");
	entities.push_back(lockerKey);
	cell->AddEntity(lockerKey);

	Item* gun = new Item("A gun.", "A reglementary weapon of prison guards dropped behind the bench", parking, "You killed the guard.");
	entities.push_back(gun);
	lockers->AddEntity(gun);

	Item* photo = new Item("Hunter's photo.", "Photografy of a hunter with a dead elephant and a text at the other side.", corridor, "The text says: The next safary will be payed with the money of this forgetful man. Since I know the code of his office is 1-5-5 I'm stealing his wallet money.");
	entities.push_back(photo);
	lockers->AddEntity(photo);

	Item* wallet = new Item("Director's wallet.", "There is a ID card, a driver's license, credit card and a note, but there is no money.", corridor, "The note says: Remember, the nursing room code changes every day. Is the date of the day it is.");
	entities.push_back(wallet);
	directors->AddEntity(wallet);

	Item* carKey = new Item("Car key.", "A key of the luxury cars' brand Porx.", parking, "If have entered in the director's car, time to say good bye to the prison.");
	entities.push_back(carKey);
	directors->AddEntity(carKey);


	
	// NPC
	NPC* prisoner = new NPC("Prisoner", "Is in bed due to a long-term injury.", nursing);
	entities.push_back(prisoner);



	// Initialization
	cout << "What's your name?" << endl;
	string playerName;
	cin >> playerName;
	cout << endl;
	Player* player = new Player(playerName, ", an innocent prisoner. Today, 14th of October, is your fist day at jail, but you decided to escape.", cell, entities);
	cout << "What do you want to do now, " << playerName << "? Press H if you need help in any moment." << endl;

	bool finished = false;
	
	while (!finished && !player->escaped)
	{
		string action;
		cin >> action;
		cout << endl;

		if (action[0] == 'h' || action[0] == 'H')
		{
			player->Help();
		}
		else if (action[0] == 'l' || action[0] == 'L')
		{
			player->Look();
		}
		else if (action[0] == 'g' || action[0] == 'G')
		{
			player->Go();
		}
		else if (action[0] == 's' || action[0] == 'S')
		{
			player->Search();
		}
		else if (action[0] == 'p' || action[0] == 'P')
		{
			player->Pick();
		}
		else if (action[0] == 'd' || action[0] == 'D')
		{
			player->Drop();
		}
		else if (action[0] == 'u' || action[0] == 'U')
		{
			player->Use();
		}
		else if (action[0] == 'o' || action[0] == 'O')
		{
			player->Open();
		}
		else if (action[0] == 't' || action[0] == 'T')
		{
			if (player->location == nursing)
				player->Talk();
		}
		else if (action[0] == 'e' || action[0] == 'E')
		{
			if (player->location == parking && player->car == true)
				player->Escape();
		}
		else if (action[0] == 'f' || action[0] == 'F')
		{
			cout << "You have accepted an unjust condemn." << endl;
			finished = true;
		}
		else
		{
			cout << "Sorry I didn't understand. Press H if you need help." << endl;
		}
	}
}

World::~World()
{

}