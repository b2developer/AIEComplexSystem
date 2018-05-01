#pragma once
#include "Data.h"

/*
* class FloatData
* child class of BaseData
*
* a data point for an account that is a floating point number
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018s
*/
class FloatData : public BaseData
{
public:

	float data = 0.0f;

	/*
	* FloatData()
	* default constructor
	*/
	FloatData() {}

	/*
	* ~FloatData()
	* default destructor
	*/
	~FloatData() {}

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
		string serial = name + ",@f" + to_string(data);

		return serial;
	}
};