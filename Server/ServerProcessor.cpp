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

	listener.setBlocking(true);
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

			//attempt to recieve data from the client
			while (socket->receive(rv) != Socket::Done) 
			{
				//cancel the loop if the first iteration doesn't get any data
				if (rv.getDataSize() == 0)
				{
					break;
				}
			}

			//check if data was recieved
			if (rv.getDataSize() > 0)
			{
				string packet = (char*)rv.getData();
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
					string packet = "@failure";
					socket->send(packet.c_str(), packet.size());
				}
				else if (command == "@create") //creation and the account wasn't found = SUCCESS
				{
					string packet = "@success";
					socket->send(packet.c_str(), packet.size());

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

					string packet = "@success";
					socket->send(packet.c_str(), packet.size());
				}
				else if (command == "@create") //creation and the account wasn't found = FAILURE
				{
					string packet = "@failure";
					socket->send(packet.c_str(), packet.size());
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
