#include "IntData.h"

//convert to string
string IntData::toString()
{
	string serial = name + ",@i" + to_string(data);

	return serial;
}

//test if the string can be deserialised
bool IntData::canDeserialise(string data)
{
	vector<string> parts = split(data, ',');

	//check that the data is long enough
	if (parts[1].length() >= 3)
	{
		string sub = parts[1].substr(0, 2);

		//check the data tag
		if (sub == "@i")
		{
			return true;
		}
	}

	return false;
}

//create data out of it's string form
BaseData* IntData::deserialise(string data)
{
	vector<string> parts = split(data, ',');

	string sub = parts[1].substr(2, parts[1].length() - 2);

	IntData* i = new IntData();
	i->name = parts[0];
	i->data = atoi(sub.c_str());

	return i;
}