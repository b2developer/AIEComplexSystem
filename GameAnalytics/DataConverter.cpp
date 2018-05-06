#include "DataConverter.h"

#include "IntData.h"
#include "FloatData.h"
#include "StringData.h"
#include "ArrayData.h"
#include "MatrixData.h"

//constructor
DataConverter::DataConverter()
{
	convertors.push_back(new IntData());
	convertors.push_back(new FloatData());
	convertors.push_back(new StringData());
	convertors.push_back(new ArrayData());
	convertors.push_back(new MatrixData());
}

//destructor
DataConverter::~DataConverter()
{
	size_t conSize = convertors.size();

	//delete all convertors
	for (size_t i = 0; i < conSize; i++)
	{
		delete convertors[i];
	}
}

//singleton retrieval
DataConverter * DataConverter::getInstance()
{
	static DataConverter* singleton = nullptr;

	//create the singleton if it hasn't already been created
	if (singleton == nullptr)
	{
		singleton = new DataConverter();
	}

	return singleton;
}

//convert serial to an object
BaseData * DataConverter::deserialise(string data)
{
	size_t conSize = convertors.size();

	//test all convertors
	for (size_t i = 0; i < conSize; i++)
	{
		BaseData* conv = convertors[i];

		//attempt to deserialise with the convertor
		if (conv->canDeserialise(data))
		{
			return conv->deserialise(data);
		}
	}

	return nullptr;
}