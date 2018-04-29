#pragma once
#include <string>
#include <vector>
#include "Data.h"

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

	//list of data
	vector<BaseData*> datapoints;

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
	*/
	void deserialise(string data);

	/*
	* overwriteData
	*
	* replaces the datapoint with the given type and name with the new data
	*
	* @param string name - the name of the datapoint
	* @param EDataType type - the variable type of the data
	* @param void* newData - void pointer to the new value
	* @returns void
	*/
	void overwriteData(string name, EDataType type, void* newData);

	/*
	* offsetData
	*
	* updates the datapoint with a relative value
	* (fails on strings)
	*
	* @param string name - the name of the datapoint
	* @param EDataType type - the variable type of the data
	* @param void* newData - void pointer to the offset value
	* @returns void
	*/
	void offsetData(string name, EDataType type, void* newData);
};