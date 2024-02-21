#pragma once
#include <iostream>
#include "TaskList.h"

class Menu
{
private:
	TaskList tl;
	string user;
public:
	Menu();
	char ask();
	~Menu();
	bool loop();
	void updateTaskList();
	void writeInFile();
};
