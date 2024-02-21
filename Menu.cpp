#include "Menu.h"
#include <string>
#include <fstream>
#include <cstdio>

Menu::Menu()
{
	cout << "********************************************************" << endl;
	cout << "*             WELCOME TO Your ToDo List                *" << endl;
	cout << "********************************************************" << "\tby Paul Popescu" << endl << endl << endl;
	cout << "Login with your file name(where your tasks will be saved)\n";
	getline(cin, user);
	cout << "Did you log in before with this name? (Y/N)\n*Saying no will delete data if you actually did. ";
	char resp;
	cin >> resp;
	user += ".bin";
	if (resp == 'y' || resp == 'Y')
	{
		updateTaskList();
	}
}

char Menu::ask()
{
	cout << "What are you about?\n\n";
	cout << "(V)iew tasks\n";
	cout << "(A)dd new task\n";
	cout << "(U)pdate task\n";
	cout << "(D)elete task\n";
	cout << "(E)xit ToDo list\n";
	char resp;
	cin >> resp;
	return resp;
}

Menu::~Menu()
{
	string userName = user.substr(0, user.length() - 4);
	cout << "\nGoodbye, " << userName << "!" << endl;
	writeInFile();
}

bool Menu::loop()
{
	Task t;
	int num;
	int exit = 0;
	while (exit == 0)
	{
		switch (ask())
		{
		default:
			throw exception("Invalid command!\n");
			return 1;
		case 'v':
		case 'V':
			tl.showAll();
			return 1;
		case 'a':
		case 'A':
			cin >> t;
			tl.append(t);
			return 1;
		case 'u':
		case 'U':
			tl.showAll();
			cout << "Which task are you willing to update? (specify number): ";
			cin >> num;
			tl.update(num);
			return 1;
		case 'd':
		case 'D':
			tl.showAll();
			cout << "Which task are you willing to delete? (specify number): ";
			cin >> num;
			tl.deleteTask(num);
			return 1;
		case 'e':
		case 'E':
			exit = 1;
			return 0;
		}
	}
}

void Menu::updateTaskList()
{
	try
	{
		tl.deserializeAll(user);
	}
	catch (NoAccountException e)
	{
		cerr << e.what();
	}
}

void Menu::writeInFile()
{
	tl.serializeAll(user);
}