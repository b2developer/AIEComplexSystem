#include "AccountInfo.h"
#include "StringHelper.h"

//constructor
AccountInfo::AccountInfo()
{

}

//destructor
AccountInfo::~AccountInfo()
{

}

//object to string
string AccountInfo::serialise()
{
	string serial = string{};

	serial += name;
	serial += ",";
	serial += pass;

	return serial;

}

//string to object initialisation
void AccountInfo::deserialise(string data)
{
	vector<string> subs = split(data, ',');

	name = subs[0];
	pass = subs[1];
}
