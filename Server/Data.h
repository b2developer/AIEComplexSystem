#pragma once
#include <string>
#include <sstream>

using namespace std;

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
	BaseData() {}

	/*
	* ~BaseData()
	* default destructor
	*/
	virtual ~BaseData() {}

	/*
	* toString
	* abstract function
	*
	* serialises the data into a string
	*
	* @returns string - string representation of the data
	*/
	virtual string toString() = 0;
};