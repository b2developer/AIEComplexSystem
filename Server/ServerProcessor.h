#pragma once
#include <vector>
#include <string>
#include <SFML\Network.hpp>

#include "AccountInfo.h"

using namespace std;
using namespace sf;

//port to bind the server to
const int COMMUNICATION_PORT = 5000;
const int COMMUNICATION_SIZE = 256;

/*
* class ServerProcessor
*
* central manager object of the server, keeps track of all connections 
* and communication between all connected clients
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018
*/
class ServerProcessor
{
public:

	TcpListener listener;

	//both vectors contain associated data, each socket corelates to the account info
	vector<TcpSocket*> sockets;
	vector<AccountInfo*> loggedAccounts;

	/*
	* ServerProcessor()
	* constructor, binds the server
	*/
	ServerProcessor();

	/*
	* ~ServerProcessor()
	* destructor, closes the server
	*/
	~ServerProcessor();

	/*
	* run
	*
	* starts a loop that ends when no users are connected
	*
	* @returns void
	*/
	void run();

	/*
	* processRequest
	*
	* examines the string containing the desired command
	* and responds appropriately
	*
	* @param string data - the command to decypher and respond to
	* @param int i - the index of the socket that sent the request
	* @returns void
	*/
	void processRequest(string data, int i);
};