#include "StringHelper.h"

//splits the string into sub-strings seperated by the split char
vector<string> split(string data, char split)
{
	size_t len = data.length();
	size_t start = 0;
	
	vector<string> substrs{};
	
	//iterate through the string, checking for the split char and creating a substring
	for (size_t i = 0; i < len; i++)
	{
		//split char has been foundeg
		if (data[i] == split)
		{
			string substr = data.substr(start, i - start);
			substrs.push_back(substr);
			start = i + 1;
		}
	}

	string substr = data.substr(start, len - start);
	substrs.push_back(substr);
	
	return substrs;
}