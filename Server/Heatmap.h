#pragma once
#include "Data.h"

//data type used to update a heat-map
struct HeatMapData
{
	int x;
	int y;
	int** v;

	//operator overload for adding heatmaps
	void operator+=(const HeatMapData& other)
	{
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				v[i][j] += other.v[i][j];
			}
		}
	}
};

/*
* class HeatMap
* child class of BaseData
*
* a data point for a 2D array of ints, becomes normalised and
* can then be rendered into an image
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018s
*/
class HeatMap : public BaseData
{
public:

	HeatMapData * data;

	/*
	* HeatMap()
	* default constructor
	*/
	HeatMap() {}

	/*
	* ~HeatMap()
	* destructor, deallocates the array
	*/
	~HeatMap()
	{
		delete data;
	}

	/*
	* toString
	* overrides BaseData's toString()
	*
	* serialises the data into a string
	*
	* @returns string - string representation of the data
	*/
	string toString() override
	{
		string serial = name + ",@h";

		string s = to_string(data->x);

		serial += s;
		serial += ".";

		s = to_string(data->y);

		serial += s;

		s = "";

		//serialise the 2D array with '.' as the delimiter
		for (int i = 0; i < data->y; i++)
		{
			for (int j = 0; j < data->x; j++)
			{
				serial += ".";
				s = to_string(data->v[i][j]);;
				serial += s;
			}
		}

		return serial;
	}
};