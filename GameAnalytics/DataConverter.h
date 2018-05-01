#pragma once
#include <string>
#include <vector>

#include "Data.h"

using namespace std;

#define DC DataConverter::getInstance()

/*
* class DataConverter
*
* singleton that is responsible for automated serialisation of variables
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018
*/
class DataConverter
{
private:

	/*
	* DataConverter()
	* constructor, holds all converters
	*/
	DLL_EXP DataConverter();

	/*
	* ~DataConverter()
	* destructor, removes all converters
	*/
	DLL_EXP ~DataConverter();

public:

	vector<BaseData*> convertors;

	/*
	* getInstance
	*
	* gets a pointer to the only instance of the game analytics object,
	* creates the object if it doesn't already exist
	*
	* @returns static DataConverter* - pointer to the singleton
	*/
	DLL_EXP static DataConverter* getInstance();

	/*
	* deserialise
	*
	* turns a string into a base data object
	* returns nullptr if the string can't be converted
	*
	* @param string data - the serialised object to be converted
	* @returns BaseData* - pointer to the deserialised form
	*/
	DLL_EXP BaseData* deserialise(string data);
};