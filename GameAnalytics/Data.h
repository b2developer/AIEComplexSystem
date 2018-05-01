#pragma once
#include <string>
#include <sstream>
#include "StringHelper.h"

using namespace std;

#include "dllimport.h"

enum class EDataType
{
	INT,
	FLOAT,
	STRING,
	HEATMAP,
};

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
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018s
*/
class BaseData
{
public:

	//name of the data
	string name;

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
	* wrap
	* abstract function
	*
	* takes a piece of data and attempts to create a BaseData object out of it
	*
	* @param void* data - pointer to the data
	* @returns BaseData* - pointer to the wrapped data
	*/
	DLL_EXP virtual BaseData* wrap(void* data) = 0;
};