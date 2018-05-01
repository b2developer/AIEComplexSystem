#pragma once
#include "Data.h"

/*
* class StringData
* child class of BaseData
*
* a data point for an account that is a string
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018s
*/
class StringData : public BaseData
{
public:

	string data;

	/*
	* StringData()
	* default constructor
	*/
	StringData() {}

	/*
	* ~StringData()
	* default destructor
	*/
	~StringData() {}

	/*
	* toString
	* overrides BaseData's toString()
	*
	* serialises the data into a string
	*
	* @returns string - string representation of the data
	*/
	string toString() override
	{
		string s;
		s += data;

		string serial = name + "," + "@s" + s;

		return serial;
	}
};