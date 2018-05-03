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

	client = new sf::TcpSocket();
	client->setBlocking(true);

	while (true)
	{
		string ip;

		std::cout << "Enter an IP Address: ";
		std::cin >> ip;

		//get the local host
		sf::IpAddress destination = sf::IpAddress::getLocalAddress();

		//the user entered a manual ip, use that instead
		if (ip != "local")
		{
			destination = sf::IpAddress(ip.c_str());
		}

		std::cout << "Connecting to Server...\n";

		//return the result of the connection attempt
		if (client->connect(destination, COMMUNICATION_PORT) == sf::Socket::Done)
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

		string packetStr = "@" + mode + "," + username + ',' + password;
		sf::Packet packet = sf::Packet();

		packet.append(packetStr.c_str(), packetStr.length());

		client->send(packet);

		sf::Packet rv;

		//wait for the response
		if (client->receive(rv) == sf::Socket::Done)
		{
			size_t rvs = rv.getDataSize();
			std::string rev_packet_s = (char*)rv.getData();
			rev_packet_s.resize(rvs);
		
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

	client->setBlocking(false);

	connected = true;

	return true;
}

//attempts to send a data update to the server
void GameAnalytics::updateData(BaseData* data, EUpdate updateType)
{
	string packetData;

	if (updateType == EUpdate::OVERWRITE)
	{
		packetData = "@overwrite,";
	}
	else if (updateType == EUpdate::OFFSET)
	{
		packetData = "@offset,";
	}

	packetData += data->toString();

	//loop and send
	sf::Packet packet = sf::Packet();
	packet.append(packetData.c_str(), packetData.length());

	
	sf::Socket::Status status = client->send(packet);

	while (status != sf::Socket::Done && status != sf::Socket::Disconnected) 
	{
		status = client->send(packet);
	}

	//the server has become disconnected
	if (status == sf::Socket::Disconnected)
	{
		connected = false;
	}
}
