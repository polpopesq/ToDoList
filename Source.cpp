#include "Menu.h"

using namespace std;

int main()
{
	bool stay = true;
	Menu mainMenu;
	while(stay)
	try
	{
		stay = mainMenu.loop();
	}
	catch (exception e)
	{
		cerr << e.what();
	}
	return 0;
}