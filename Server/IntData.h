#pragma once
#include "Data.h"

/*
* class IntData
* child class of BaseData
*
* a data point for an account that is an interger
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018s
*/
class IntData : public BaseData
{
public:

	int data = 0;

	/*
	* IntData()
	* default constructor
	*/
	IntData() {}

	/*
	* ~IntData()
	* default destructor
	*/
	~IntData() {}

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
		string serial = name + ",@i" + to_string(data);

		return serial;
	}
};