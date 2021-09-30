#include "menu.h"
#include "data.h"
#include <thread>

int main()
{    
	//���������˻�
	User user("user", "123");
	Menu menu;
	users.push_back(user);
	actuser = user;

	thread frontThread(&Menu::welcome, menu);
	thread backThread(opt::stock::getStocksData);
	
	frontThread.join();
	backThread.join();
	
}