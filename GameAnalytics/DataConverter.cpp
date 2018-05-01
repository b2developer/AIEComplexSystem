#include "DataConverter.h"

#include "IntData.h"
#include "FloatData.h"
#include "StringData.h"

//constructor
DataConverter::DataConverter()
{
	convertors.push_back(new IntData());
	convertors.push_back(new FloatData());
	convertors.push_back(new StringData());
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

//convert data to an object
DLL_EXP BaseData * DataConverter::wrap(void * data)
{
	size_t conSize = convertors.size();

	//test all convertors
	for (size_t i = 0; i < conSize; i++)
	{
		BaseData* conv = convertors[i];
		BaseData* attempt = conv->wrap(data);

		//check if the cast worked
		if (attempt != nullptr)
		{
			return attempt;
		}
	}

	return nullptr;
}
