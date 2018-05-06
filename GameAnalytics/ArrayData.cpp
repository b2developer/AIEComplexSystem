#include "ArrayData.h"
#include "Delimiter.h"

//destructor
ArrayData::~ArrayData()
{
	delete[] data;
}

//convert to string
string ArrayData::toString()
{
	string serial = name + delimiter + "@a";

	serial += to_string(sizeI);
	serial += listDelimiter;
	serial += to_string(sizeJ);

	for (int i = 0; i < sizeI * sizeJ; i++)
	{
		serial += listDelimiter;
		serial += to_string(data[i]);
	}

	return serial;
}

//test if the string can be deserialised
bool ArrayData::canDeserialise(string data)
{
	vector<string> parts = split(data, delimiter.c_str()[0]);

	//check that the data is long enough
	if (parts[1].length() >= 3)
	{
		string sub = parts[1].substr(0, 2);

		//check the data tag
		if (sub == "@a")
		{
			return true;
		}
	}

	return false;
}

//create data out of it's string form
BaseData * ArrayData::deserialise(string data)
{
	vector<string> parts = split(data, delimiter.c_str()[0]);

	string sub = parts[1].substr(2, parts[1].length() - 2);

	//split the list into individual entries
	vector<string> entries = split(sub, listDelimiter.c_str()[0]);

	ArrayData* a = new ArrayData();

	a->name = parts[0];

	a->sizeI = atoi(entries[0].c_str());
	a->sizeJ = atoi(entries[1].c_str());

	int size = a->sizeI * a->sizeJ;

	a->data = new int[size];

	//assign all of the ints in the array
	for (int i = 0; i < size; i++)
	{
		a->data[i] = atoi(entries[i + 2].c_str());
	}

	return a;
}

//addition overload
void ArrayData::add(BaseData * other)
{
	ArrayData* conv = (ArrayData*)other;

	//check that the sizes are identical
	if (sizeI == conv->sizeI && sizeJ == conv->sizeJ)
	{
		//2D addition loop
		for (int i = 0; i < sizeI * sizeJ; i++)
		{
			data[i] += conv->data[i];
		}
	}
}

