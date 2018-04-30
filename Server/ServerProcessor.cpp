#include "ServerProcessor.h"

#include <iostream>
#include "StringHelper.h"
#include "AccountManager.h"
#include "Heatmap.h"

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
				packet[rev_s] = '\0';
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
				string dataName = parts[1];
				string type = parts[2].substr(0, 2);
				string data = parts[2].substr(2, parts[2].size() - 2);

				if (type == "@i")
				{
					int i = atoi(data.c_str());

					info->overwriteData(dataName, EDataType::INT, &i);
				}
				else if (type == "@f")
				{
					float f = atof(data.c_str());

					info->overwriteData(dataName, EDataType::FLOAT, &f);
				}
				else if (type == "@s")
				{
					info->overwriteData(dataName, EDataType::STRING, &data);
				}
				else if (type == "@h")
				{
					HeatMapData h = HeatMapData();

					vector<string> dataParts = split(data, '.');

					h.x = atoi(dataParts[0].c_str());

					h.y = atoi(dataParts[1].c_str());

					//create the columns
					h.v = new int*[h.y];

					for (int i = 0; i < h.y; i++)
					{
						//create the rows
						h.v[i] = new int[h.x];

						for (int j = 0; j < h.x; j++)
						{
							h.v[i][j] = atoi(dataParts[2 + i * h.x + j].c_str());
						}
					}

					info->overwriteData(dataName, EDataType::HEATMAP, &h);
				}

				AM->save();
			}
			else if (command == "@offset")
			{
				string dataName = parts[1];
				string type = parts[2].substr(0, 2);
				string data = parts[2].substr(2, parts[2].size() - 2);

				if (type == "@i")
				{
					int i = atoi(data.c_str());

					info->offsetData(dataName, EDataType::INT, &i);
				}
				else if (type == "@f")
				{
					float f = atof(data.c_str());

					info->offsetData(dataName, EDataType::FLOAT, &f);
				}
				else if (type == "@s")
				{
					//can't update strings this way
				}
				else if (type == "@h")
				{
					HeatMapData h = HeatMapData();

					vector<string> dataParts = split(data, '.');

					h.x = atoi(dataParts[0].c_str());

					h.y = atoi(dataParts[1].c_str());

					//create the columns
					h.v = new int*[h.y];

					for (int i = 0; i < h.y; i++)
					{
						//create the rows
						h.v[i] = new int[h.x];

						for (int j = 0; j < h.x; j++)
						{
							h.v[i][j] = atoi(dataParts[2 + i * h.x + j].c_str());
						}
					}

					info->offsetData(dataName, EDataType::HEATMAP, &h);
				}

				AM->save();
			}
		}
	}
}
