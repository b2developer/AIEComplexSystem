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
	DLL_EXP FloatData() {}

	/*
	* ~FloatData()
	* default destructor
	*/
	DLL_EXP ~FloatData() {}

	/*
	* toString
	* overrides BaseData's toString()
	*
	* serialises the data into a string
	*
	* @returns string - string representation of the data
	*/
	DLL_EXP string toString() override
	{
		string serial = name + ",@f" + to_string(data);

		return serial;
	}

	/*
	* canDeserialise
	* overrides BaseData's canDeserialise(string data)
	*
	* checks if this data type can deserialise the data
	*
	* @param string data - the serialised data object
	* @returns bool - result of the check
	*/
	DLL_EXP bool canDeserialise(string data) override
	{
		vector<string> parts = split(data, ',');

		//check that the data is long enough
		if (parts[1].length() >= 3)
		{
			string sub = parts[1].substr(0, 2);

			//check the data tag
			if (sub == "@f")
			{
				return true;
			}
		}

		return false;
	}

	/*
	* deserialise
	* overrides BaseData's deserialise(string data)
	*
	* generates a deserialised version of the string
	*
	* @param string data - the serialised data object
	* @returns BaseData* - deserialised vesion of the string
	*/
	DLL_EXP BaseData* deserialise(string data) override
	{
		vector<string> parts = split(data, ',');

		string sub = parts[1].substr(2, parts[1].length() - 2);

		FloatData* f = new FloatData();
		f->name = parts[0];
		f->data = (float)atof(sub.c_str());

		return f;
	}

	/*
	* wrap
	* overrides BaseData's wrap(void* data)
	*
	* takes a piece of data and attempts to create a BaseData object out of it
	*
	* @param void* data - pointer to the data
	* @returns BaseData* - pointer to the wrapped data
	*/
	DLL_EXP BaseData* wrap(void* data) override
	{
		float* con = (float*)data;

		//check that the cast worked
		if (con != nullptr)
		{
			FloatData* d = new FloatData();
			d->data = *con;

			return d;
		}

		return nullptr;
	}
};