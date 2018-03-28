#include "ServerProcessor.h"

#include <iostream>
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
			s->setBlocking(false);
			sockets.push_back(s);
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

			char packet[COMMUNICATION_SIZE];
			size_t rev_s = 0;

			//attempt to recieve data from the client
			if (socket->receive(packet, COMMUNICATION_SIZE, rev_s) == Socket::Done)
			{
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
		//login commands are only processed if the user hasn't logged in
		if (command == "@login")
		{

		}
	}
	else
	{

	}
}
