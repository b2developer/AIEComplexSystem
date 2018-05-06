#pragma once
#include "Data.h"

/*
* class ArrayData
* child class of BaseData
*
* a data point for an account that is a 1D or 2D array of intergers
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018s
*/
class ArrayData : public BaseData
{
public:

	//size of the array
	int sizeI = 0;
	int sizeJ = 0;

	int* data;

	/*
	* ArrayData()
	* constructor, initialises isArray flag to true
	*/
	DLL_EXP ArrayData()
	{
		isArray = true;
	}


	/*
	* ~ArrayData()
	* destructor, assigns the array space
	*/
	DLL_EXP ~ArrayData();

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

	/*
	* add
	* overrides BaseData's add(BaseData& other)
	*
	* adds a data source to another
	*
	* @param BaseData* other - reference to the other data to add
	* @returns void
	*/
	DLL_EXP virtual void add(BaseData* other) override;
};