#include "MatrixData.h"
#include "Delimiter.h"

//destructor
MatrixData::~MatrixData()
{
	delete[] data;
}

//convert to string
string MatrixData::toString()
{
	string serial = name + delimiter + "@m";

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
bool MatrixData::canDeserialise(string data)
{
	vector<string> parts = split(data, delimiter.c_str()[0]);

	//check that the data is long enough
	if (parts[1].length() >= 3)
	{
		string sub = parts[1].substr(0, 2);

		//check the data tag
		if (sub == "@m")
		{
			return true;
		}
	}

	return false;
}

//create data out of it's string form
BaseData * MatrixData::deserialise(string data)
{
	vector<string> parts = split(data, delimiter.c_str()[0]);

	string sub = parts[1].substr(2, parts[1].length() - 2);

	//split the list into individual entries
	vector<string> entries = split(sub, listDelimiter.c_str()[0]);

	MatrixData* m = new MatrixData();

	m->name = parts[0];

	m->sizeI = atoi(entries[0].c_str());
	m->sizeJ = atoi(entries[1].c_str());

	int size = m->sizeI * m->sizeJ;

	m->data = new float[size];

	//assign all of the ints in the array
	for (int i = 0; i < size; i++)
	{
		m->data[i] = (float)atof(entries[i + 2].c_str());
	}

	return m;
}

//addition overload
void MatrixData::add(BaseData * other)
{
	MatrixData* conv = (MatrixData*)other;

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

