#pragma once
#include <string>

using namespace std;

//constant c-string sizes
const int NAME_SIZE = 50;
const int PASS_SIZE = 15;

/*
* class AccountInfo
*
* deserialisation object for account data stored in a text file
* contains the name, password and all events and data that was triggered by the client
*
* @author: BradleyBooth, Academy of Interactive Entertainment, 2018
*/
class AccountInfo
{
public:

	string name; //username c-string
	string pass; //password c-string

	/*
	* AccountInfo()
	* default constructor
	*/
	AccountInfo();

	/*
	* ~AccountInfo()
	* default destructor
	*/
	~AccountInfo();

	/*
	* serialise
	*
	* turns the object into a string that represents the data it holds
	*
	* @returns string - a serialsied version of the object
	*/
	string serialise();

	/*
	* deserialise
	*
	* uses serial data to initialise the object
	*
	* @param string data - the data used to 
	a
	*/
	void deserialise(string data);
};