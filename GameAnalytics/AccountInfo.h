#pragma once
#include <string>
#include <vector>
#include "dllimport.h"

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
	string key; //additional access

	//list of data
	vector<BaseData*> datapoints;

	/*
	* AccountInfo()
	* default constructor
	*/
	DLL_EXP AccountInfo();

	/*
	* ~AccountInfo()
	* default destructor
	*/
	DLL_EXP ~AccountInfo();

	/*
	* serialise
	*
	* turns the object into a string that represents the data it holds
	*
	* @returns string - a serialsied version of the object
	*/
	DLL_EXP string serialise();

	/*
	* deserialise
	*
	* uses serial data to initialise the object
	*
	* @param string data - the data used to 
	*/
	DLL_EXP void deserialise(string data);

	/*
	* overwriteData
	*
	* replaces the datapoint with the given type and name with the new data
	*
	* @param BaseData* bd - the data to replace
	* @returns void
	*/
	DLL_EXP void overwriteData(BaseData* bd);

	/*
	* offsetData
	*
	* updates the datapoint with a relative value
	* (fails on strings)
	*
	* @param BaseData* bd - the data to replace
	* @returns void
	*/
	DLL_EXP void offsetData(BaseData* bd);
};