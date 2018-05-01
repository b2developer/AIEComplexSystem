#include "FloatData.h"

//convert to string
string FloatData::toString()
{
	string serial = name + ",@f" + to_string(data);

	return serial;
}

//test if the string can be deserialised
bool FloatData::canDeserialise(string data)
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

//create data out of it's string form
BaseData * FloatData::deserialise(string data)
{
	vector<string> parts = split(data, ',');

	string sub = parts[1].substr(2, parts[1].length() - 2);

	FloatData* f = new FloatData();
	f->name = parts[0];
	f->data = (float)atof(sub.c_str());

	return f;
}

