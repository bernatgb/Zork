// PrisonEscape.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "string"
#include "World.h"

using namespace std;

int main()
{
	cout << "Wellcome to the jail, do you want to escape? (Y/N)" << endl;
	string answer;
	cin >> answer;
	cout << endl;

	bool answered = false;
	while (!answered)
	{
		if (answer[0] == 'Y' || answer[0] == 'y')
		{
			answered = true;
			cout << "Ok, you are innocent it's fair trying to escape." << endl << endl;
			World world;
		}
		else if (answer[0] == 'N' || answer[0] == 'n')
		{
			answered = true;
			cout << "Ok, have... fun" << endl;
		}
		else
		{
			cout << "Sorry, I didn't understand, do you want to escape? (Y/N)" << endl;
			cin >> answer;
			cout << endl;
		}
	}
}
