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
	DLL_EXP string toString() override;
	
	/*
	* canDeserialise
	* overrides BaseData's canDeserialise(string data)
	*
	* checks if this data type can deserialise the data
	*
	* @param string data - the serialised data object
	* @returns bool - result of the check
	*/
	DLL_EXP bool canDeserialise(string data) override;

	/*
	* deserialise
	* overrides BaseData's deserialise(string data)
	*
	* generates a deserialised version of the string
	*
	* @param string data - the serialised data object
	* @returns BaseData* - deserialised vesion of the string
	*/
	DLL_EXP BaseData* deserialise(string data) override;
};