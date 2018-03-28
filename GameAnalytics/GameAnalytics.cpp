#include "GameAnalytics.h"

#include <iostream>
#include <SFML/Network.hpp>


//constructor
GameAnalytics::GameAnalytics()
{

}

//destructor
GameAnalytics::~GameAnalytics()
{

}

//singleton instance retrieval
GameAnalytics* GameAnalytics::getInstance()
{
	static GameAnalytics* singleton = nullptr;

	//create the singleton if it doesn't exist already
	if (singleton == nullptr)
	{
		singleton = new GameAnalytics();
	}

	return singleton;
}

//connection attempt
DLL_EXP bool GameAnalytics::connect()
{
	//get the local host
	sf::IpAddress local = sf::IpAddress::getLocalAddress();

	client = new sf::TcpSocket();
	client->setBlocking(false);

	//return the result of the connection attempt
	if (client->connect(local, COMMUNICATION_PORT) != sf::Socket::Done)
	{
		return false;
	}

	string username, password;

	std::cout << "Username: ";
	std::cin >> username;

	std::cout << "Password: ";
	std::cin >> password;

	std::cout << "Connecting...";

	string packet = "@login," + username + ',' + password;
	client->send(packet.c_str(), (size_t)COMMUNICATION_SIZE);

	return true;
}
