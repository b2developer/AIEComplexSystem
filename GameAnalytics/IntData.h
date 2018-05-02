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
	DLL_EXP IntData() {}

	/*
	* ~IntData()
	* default destructor
	*/
	DLL_EXP ~IntData() {}

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
	* (must be verified by canSerialise(string data))
	* generates a deserialised version of the string
	*
	* @param string data - the serialised data object
	* @returns BaseData* - deserialised vesion of the string
	*/
	DLL_EXP BaseData* deserialise(string data) override;

	/*
	* operator+=
	* overrides BaseData's add(BaseData& other)
	*
	* adds a data source to another
	*
	* @param BaseData* other - reference to the other data to add
	* @returns void
	*/
	DLL_EXP virtual void add(BaseData* other) override;
};