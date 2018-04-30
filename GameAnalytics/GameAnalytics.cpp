#include "GameAnalytics.h"

#include <iostream>
#include <sstream>
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
void GameAnalytics::updateData(string name, void* data, EDataType dataType, EUpdate updateType)
{
	string packet;

	if (updateType == EUpdate::OVERWRITE)
	{
		packet = "@overwrite," + name + ",";
	}
	else if (updateType == EUpdate::OFFSET)
	{
		packet = "@offset," + name + ",";
	}

	if (dataType == EDataType::INT)
	{
		int d = *(int*)data;

		string s = to_string(d);

		packet += "@i";
		packet += s;
	}
	else if (dataType == EDataType::FLOAT)
	{
		float d = *(float*)data;

		string s = to_string(d);

		packet += "@i";
		packet += s;
	}
	else if (dataType == EDataType::STRING)
	{
		//strings can't be offset
		if (updateType == EUpdate::OFFSET)
		{
			return;
		}

		string s = *(string*)data;

		packet += "@s";
		packet += s;
	}
	else if (dataType == EDataType::HEATMAP)
	{
		packet += "@h";

		HeatMapUpdate h = *(HeatMapUpdate*)data;

		string s = to_string(h.x);

		packet += s;
		packet += ".";

		s = to_string(h.y);

		packet += s;

		s = "";

		//serialise the 2D array with '.' as the delimiter
		for (int i = 0; i < h.y; i++)
		{
			for (int j = 0; j < h.x; j++)
			{
				packet += ".";
				s = to_string(h.v[i][j]);;
				packet += s;
			}
		}
	}

	client->send(packet.c_str(), packet.size() + 1);
}
