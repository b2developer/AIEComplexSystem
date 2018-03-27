#include "ServerProcessor.h"
#include <iostream>

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
			loggedAccounts.push_back(nullptr);

			cout << "client connected.";
		}
		else
		{
			delete s;
		}
	}
}

//processes the string as a request
void ServerProcessor::processRequest(string data)
{

}
