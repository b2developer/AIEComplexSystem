#include "AccountInfo.h"
#include "StringHelper.h"

#include "IntData.h"
#include "FloatData.h"
#include "StringData.h"
#include "Heatmap.h"

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
	serial += ",";
	serial += pass;

	size_t points = datapoints.size();

	//serialise each data point
	for (size_t i = 0; i < points; i++)
	{
		serial += ",";
		BaseData* data = datapoints[i];
		serial += data->toString();
	}

	return serial;
}

//string to object initialisation
void AccountInfo::deserialise(string data)
{
	datapoints.clear();

	vector<string> subs = split(data, ',');

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
		string n = subs[i];
		string c = subs[i+1].substr(0, 2);
		string d = subs[i+1].substr(2, subs[i+1].size() - 2);

		BaseData* bd = nullptr;

		if (c == "@i")
		{
			bd = new IntData();
			((IntData*)bd)->data = atoi(d.c_str());
		}
		else if (c == "@f")
		{
			bd = new FloatData();
			((FloatData*)bd)->data = (float)atof(d.c_str());
		}
		else if (c == "@s")
		{
			bd = new StringData();
			((StringData*)bd)->data = d;
		}
		else if (c == "@h")
		{
			bd = new HeatMap();

			HeatMapData* h = new HeatMapData();

			vector<string> dataParts = split(d, '.');

			h->x = atoi(dataParts[0].c_str());

			h->y = atoi(dataParts[1].c_str());

			//create the columns
			h->v = new int*[h->y];

			for (int i = 0; i < h->y; i++)
			{
				//create the rows
				h->v[i] = new int[h->x];

				for (int j = 0; j < h->x; j++)
				{
					h->v[i][j] = atoi(dataParts[2 + i * h->x + j].c_str());
				}
			}

			((HeatMap*)bd)->data = h;
		}

		bd->name = n;

		datapoints.push_back(bd);
	}
}

//overwrite
void AccountInfo::overwriteData(string name, EDataType type, void * newData)
{
	BaseData* bd = nullptr;

	size_t dataSize = datapoints.size();

	//search for the datapoint with the matching name, otherwise create it
	for (size_t i = 0; i < dataSize; i++)
	{
		BaseData* s = datapoints[i];

		//name match
		if (s->name == name)
		{
			bd = s;
			break;
		}
	}

	//name mismatch, create a variable for the new data
	if (bd == nullptr)
	{
		BaseData* n = nullptr;

		//determine the type
		if (type == EDataType::INT)
		{
			n = new IntData();	
		}
		else if (type == EDataType::FLOAT)
		{
			n = new FloatData();
		}
		else if (type == EDataType::STRING)
		{
			n = new StringData();
		}
		else if (type == EDataType::HEATMAP)
		{
			n = new HeatMap();
		}

		n->name = name;

		datapoints.push_back(n);

		bd = n;
	}

	//determine the type
	if (type == EDataType::INT)
	{
		int* i = (int*)newData;
		((IntData*)bd)->data = *i;
	}
	else if (type == EDataType::FLOAT)
	{
		float* f = (float*)newData;
		((FloatData*)bd)->data = *f;
	}
	else if (type == EDataType::STRING)
	{
		string* s = (string*)newData;
		((StringData*)bd)->data = *s;
	}
	else if (type == EDataType::HEATMAP)
	{
		HeatMapData* h = (HeatMapData*)newData;
		((HeatMap*)bd)->data = h;
	}
}

//update
void AccountInfo::offsetData(string name, EDataType type, void * newData)
{
	BaseData* bd = nullptr;

	size_t dataSize = datapoints.size();

	//search for the datapoint with the matching name, otherwise create it
	for (size_t i = 0; i < dataSize; i++)
	{
		BaseData* s = datapoints[i];

		//name match
		if (s->name == name)
		{
			bd = s;
			break;
		}
	}

	//name mismatch, return
	if (bd == nullptr)
	{
		return;
	}

	//determine the type
	if (type == EDataType::INT)
	{
		int* i = (int*)newData;
		((IntData*)bd)->data += *i;
	}
	else if (type == EDataType::FLOAT)
	{
		float* f = (float*)newData;
		((FloatData*)bd)->data += *f;
	}
	else if (type == EDataType::HEATMAP)
	{
		HeatMapData* h = (HeatMapData*)newData;
		*((HeatMap*)bd)->data += *h;
	}
}
