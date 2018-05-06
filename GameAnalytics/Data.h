#pragma once
#include <string>
#include <sstream>
#include "StringHelper.h"

#include "dllimport.h"

using namespace std;

enum class EUpdate
{
	OVERWRITE,
	OFFSET,
};

/*
* class BaseData
*
* base class for a data point for an account
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018
*/
class BaseData
{
public:

	//name of the data
	string name;
	bool isArray = false;

	/*
	* BaseData()
	* default constructor
	*/
	DLL_EXP BaseData() {}

	/*
	* ~BaseData()
	* default destructor
	*/
	DLL_EXP virtual ~BaseData() {}

	/*
	* toString
	* abstract function
	*
	* serialises the data into a string
	*
	* @returns string - string representation of the data
	*/
	DLL_EXP virtual string toString() = 0;

	/*
	* canDeserialise
	* abstract function
	*
	* checks if this data type can deserialise the data
	* 
	* @param string data - the serialised data object
	* @returns bool - result of the check
	*/
	DLL_EXP virtual bool canDeserialise(string data) = 0;

	/*
	* deserialise
	* abstract function
	*
	* generates a deserialised version of the string
	*
	* @param string data - the serialised data object
	* @returns BaseData* - deserialised vesion of the string
	*/
	DLL_EXP virtual BaseData* deserialise(string data) = 0;

	/*
	* add
	* abstract function
	*
	* adds a data source to another
	*
	* @param BaseData* other - pointer to the other data to add
	* @returns void
	*/
	DLL_EXP virtual void add(BaseData* other) = 0;
};