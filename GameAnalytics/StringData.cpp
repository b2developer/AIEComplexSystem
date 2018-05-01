#include "StringData.h"

//convert to string
string StringData::toString()
{
	string serial = name + "," + "@s" + data;

	return serial;
}

//test if the string can be deserialised
bool StringData::canDeserialise(string data)
{
	vector<string> parts = split(data, ',');

	//check that the data is long enough
	if (parts[1].length() >= 3)
	{
		string sub = parts[1].substr(0, 2);

		//check the data tag
		if (sub == "@s")
		{
			return true;
		}
	}

	return false;
}

//create data out of it's string form
BaseData * StringData::deserialise(string data)
{
	vector<string> parts = split(data, ',');

	string sub = parts[1].substr(2, parts[1].length() - 2);

	StringData* i = new StringData();
	i->name = parts[0];
	i->data = sub;

	return i;
}