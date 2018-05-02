#include "ServerProcessor.h"

#include <iostream>
#include "DataConverter.h"
#include "StringHelper.h"
#include "AccountManager.h"

using namespace std;

//constructor, starts the server
ServerProcessor::ServerProcessor()
{
	//bind the server
	if (listener.listen(COMMUNICATION_PORT) != Socket::Done)
	{
		//failed to bind the server
		throw "Failed to bind communications.";
	}

	listener.setBlocking(false);
}

//destructor, ends the server
ServerProcessor::~ServerProcessor()
{
	listener.close();
}

//runs the loop that controls the server
void ServerProcessor::run()
{
	while (true)
	{
		TcpSocket* s = new TcpSocket();

		//check if there is a new client joining
		if (listener.accept(*s) == Socket::Done)
		{
			sockets.push_back(s);
			s->setBlocking(false);

			loggedAccounts.push_back(nullptr);

			cout << "client connected.\n";
			
		}
		else
		{
			delete s;
		}

		size_t size = sockets.size();

		//check each socket for messages
		for (int i = 0; i < size; i++)
		{
			TcpSocket* socket = sockets[i];

			sf::Packet rv;

			Socket::Status s = socket->receive(rv);

			//nothing to recieve if this is false
			if (s != Socket::NotReady)
			{
				size_t rs = rv.getDataSize();
				string packet = (char*)rv.getData();
				packet.resize(rs);

				//attempt to recieve all of the data from the client
				while (s != Socket::Done)
				{
					s = socket->receive(rv);

					rs = rv.getDataSize();
					string append = (char*)rv.getData();

					append.resize(rs);

					packet += append;
				}

				processRequest(packet, i);
			}
		}
	}
}

//processes the string as a request
void ServerProcessor::processRequest(string data, int i)
{

	//grab the socket and account that sent the request
	TcpSocket* socket = sockets[i];
	AccountInfo* info = loggedAccounts[i];

	vector<string> parts = split(data, ',');

	string command = parts[0];

	if (info == nullptr)
	{
		//sanitise the input
		if (parts.size() == 3)
		{
			//check that the account exists
			AccountInfo* search = AM->searchAccount(parts[1], parts[2]);

			if (search == nullptr)
			{
				if (command == "@login") //login and the account wasn't found = FAILURE
				{
					string packetStr = "@failure";
					sf::Packet packet;
					packet.append(packetStr.c_str(), packetStr.length());

					while (socket->send(packet) != sf::Socket::Done) {}
				}
				else if (command == "@create") //creation and the account wasn't found = SUCCESS
				{
					string packetStr = "@success";
					sf::Packet packet;
					packet.append(packetStr.c_str(), packetStr.length());

					while (socket->send(packet) != sf::Socket::Done) {}

					//create the account and retrieve it
					AM->createAccount(parts[1], parts[2]);
					AccountInfo* n = AM->searchAccount(parts[1], parts[2]);

					loggedAccounts[i] = n;
				}
			}
			else
			{
				if (command == "@login") //login and the account was found = SUCCESS
				{
					loggedAccounts[i] = search;

					string packetStr = "@success";
					sf::Packet packet;
					packet.append(packetStr.c_str(), packetStr.length());

					while (socket->send(packet) != sf::Socket::Done) {}
				}
				else if (command == "@create") //creation and the account wasn't found = FAILURE
				{
					string packetStr = "@failure";
					sf::Packet packet;
					packet.append(packetStr.c_str(), packetStr.length());

					while (socket->send(packet) != sf::Socket::Done) {}
				}
			}
		}
	}
	else
	{
		//sanitise the input
		if (parts.size() == 3)
		{
			if (command == "@overwrite")
			{
				string data = parts[1] + "," + parts[2];
				
				BaseData* bd = DC->deserialise(data);

				info->overwriteData(bd);

				AM->save();
			}
			else if (command == "@offset")
			{
				string data = parts[1] + "," + parts[2];

				BaseData* bd = DC->deserialise(data);

				info->overwriteData(bd);

				AM->save();
			}
		}
	}
}
