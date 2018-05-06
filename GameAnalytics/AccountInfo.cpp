#include "AccountInfo.h"
#include "StringHelper.h"

#include "DataConverter.h"

#include "Delimiter.h"

//constructor
AccountInfo::AccountInfo()
{

}

//destructor
AccountInfo::~AccountInfo()
{
	size_t points = datapoints.size();

	//serialise each data point
	for (size_t i = 0; i < points; i++)
	{
		delete datapoints[i];
	}
}

//object to string
string AccountInfo::serialise()
{
	string serial = string{};

	serial += name;
	serial += delimiter;
	serial += pass;

	size_t points = datapoints.size();

	//serialise each data point
	for (size_t i = 0; i < points; i++)
	{
		serial += delimiter;
		BaseData* data = datapoints[i];
		serial += data->toString();
	}

	return serial;
}

//string to object initialisation
void AccountInfo::deserialise(string data)
{
	datapoints.clear();

	vector<string> subs = split(data, delimiter.c_str()[0]);

	name = subs[0];
	pass = subs[1];

	size_t ss = subs.size();

	//create the data points out of the strings

	/*
	* example data point: @i1
	* @i - identifier (also @f, @s)
	*/
	for (size_t i = 2; i < ss; i+=2)
	{
		string data = subs[i] + delimiter + subs[i + 1];

		BaseData* bd = DC->deserialise(data);

		datapoints.push_back(bd);
	}
}

//overwrite
void AccountInfo::overwriteData(BaseData* bd)
{
	size_t dataSize = datapoints.size();

	//search for the datapoint with the matching name, otherwise create it
	for (size_t i = 0; i < dataSize; i++)
	{
		BaseData* s = datapoints[i];

		//name match
		if (s->name == bd->name)
		{
			delete s;
			datapoints[i] = bd;
			return;
		}
	}

	//create a new data point
	datapoints.push_back(bd);
}

//update
void AccountInfo::offsetData(BaseData* bd)
{
	size_t dataSize = datapoints.size();

	//search for the datapoint with the matching name, otherwise create it
	for (size_t i = 0; i < dataSize; i++)
	{
		BaseData* s = datapoints[i];

		//name match
		if (s->name == bd->name)
		{
			datapoints[i]->add(bd);
			delete bd;
			break;
		}
	}
}
