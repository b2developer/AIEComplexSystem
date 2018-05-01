#include "GameAnalytics.h"

#include <iostream>
#include <sstream>
#include <SFML/Network.hpp>

#include "DataConverter.h"

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
bool GameAnalytics::connect()
{
	//get the local host
	sf::IpAddress local = sf::IpAddress::getLocalAddress();

	client = new sf::TcpSocket();
	client->setBlocking(true);

	while (true)
	{
		std::cout << "Connecting to Server...\n";

		//return the result of the connection attempt
		if (client->connect(local, COMMUNICATION_PORT) == sf::Socket::Done)
		{
			std::cout << "Connection successful.\n";
			break;
		}

		std::cout << "Connection failed. Trying again..\n";
	}

	//infinite loop to login until successful
	while (true)
	{
		string mode, username, password;

		std::cout << "Mode: ";
		std::cin >> mode;

		//sanitise the input
		if (mode != "login" && mode != "create")
		{
			continue;
		}

		std::cout << "Username: ";
		std::cin >> username;

		std::cout << "Password: ";
		std::cin >> password;

		std::cout << "Logging in...";

		string packet = "@" + mode + "," + username + ',' + password;
		client->send(packet.c_str(), packet.size());

		char rev_packet[COMMUNICATION_SIZE];
		size_t rev_s;

		//wait for the response
		if (client->receive(rev_packet, (size_t)COMMUNICATION_SIZE, rev_s) == sf::Socket::Done)
		{
			rev_packet[rev_s] = '\0';
			std::string rev_packet_s = std::string(rev_packet);
		
			//examine the response
			if (rev_packet_s == "@success")
			{
				break;
			}
			else if (rev_packet_s == "@failure")
			{
				std::cout << "Login failed (bad password/account).\n";
				continue;
			}
		}

		std::cout << "Login failed.\n";
	}

	std::cout << "Login successful.\n";

	return true;
}

//attempts to send a data update to the server
void GameAnalytics::updateData(string name, void* data, EUpdate updateType)
{
	BaseData* bd = DC->wrap(data);

	//unsupported type
	if (bd == nullptr)
	{
		return;
	}

	string packet;

	bd->name = name;

	if (updateType == EUpdate::OVERWRITE)
	{
		packet = "@overwrite,";
	}
	else if (updateType == EUpdate::OFFSET)
	{
		packet = "@offset,";
	}

	packet += bd->toString();

	delete bd;

	client->send(packet.c_str(), packet.size() + 1);
}
