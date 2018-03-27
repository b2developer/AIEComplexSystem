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

	AM->createAccount("elmo", "yes");
	AM->createAccount("rick", "and morty i guess");
	AM->removeAccount("elmo", "yes");

	ServerProcessor* app = new ServerProcessor();

	app->run();
	
	AM->save();

	return 0;
}