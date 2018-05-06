#include <iostream>
#include <string>

#include "ServerProcessor.h"
#include "AccountManager.h"

#include <SFML\Network.hpp>

using namespace sf;

//Server

int main()
{
	//initialises the account manager
	AM;

	ServerProcessor* serverApp = new ServerProcessor();

	serverApp->run();
	
	AM->save();

	return 0;
}