#include "HeatmapReport.h"
#include "AccountManager.h"

#include "ArrayData.h"
#include "MatrixData.h"

#include <iostream>
#include <fstream>

//destructor
HeatmapReport::~HeatmapReport()
{
	delete[] values;
}

//sets up the data
void HeatmapReport::initialise(string table, bool normalise)
{
	size_t accountLen = AM->accounts.size();

	enum class EArrayType
	{
		NONE,
		INT,
		FLOAT,
	};

	EArrayType identifiedType = EArrayType::NONE;

	//get the data from all accounts
	for (size_t i = 0; i < accountLen; i++)
	{
		AccountInfo* account = AM->accounts[i];
		BaseData* bd = nullptr;
		size_t dataLen = account->datapoints.size();

		//search for the data
		for (size_t j = 0; j < dataLen; j++)
		{
			BaseData* t = account->datapoints[j];

			//name match
			if (t->name == table)
			{
				bd = t;
				break;
			}
		}

		//type still needs identifying (can be array or matrix)
		if (identifiedType == EArrayType::NONE)
		{
			ArrayData* a = dynamic_cast<ArrayData*>(bd);
			MatrixData* m = dynamic_cast<MatrixData*>(bd);

			//deduct the discovered type
			if (a != nullptr)
			{
				identifiedType = EArrayType::INT;

				sizeI = a->sizeI;
				sizeJ = a->sizeJ;
				values = new float[a->sizeI * a->sizeJ];

				//zero initialise
				for (size_t x = 0; x < sizeI * sizeJ; x++)
				{
					values[x] = 0.0f;
				}
			}
			else if (m != nullptr)
			{
				identifiedType = EArrayType::FLOAT;

				sizeI = m->sizeI;
				sizeJ = m->sizeJ;
				values = new float[m->sizeI * m->sizeJ];

				//zero initialise
				for (size_t x = 0; x < sizeI * sizeJ; x++)
				{
					values[x] = 0.0f;
				}
			}
		}

		//normalise the array (if needed then add it to the sum)
		if (identifiedType == EArrayType::INT)
		{
			ArrayData* a = (ArrayData*)bd;

			//store in a temp float array then normalise
			if (normalise)
			{
				float* temp = new float[sizeI * sizeJ];

				//zero initialise
				for (size_t x = 0; x < sizeI * sizeJ; x++)
				{
					temp[x] = 0.0f;
				}

				add(temp, a->data, sizeI * sizeJ);

				float m = maxValue(temp, sizeI * sizeJ);

				multiply(temp, 1 / m, sizeI * sizeJ);

				add(values, temp, sizeI * sizeJ);

				delete[] temp;
			}
			else
			{
				add(values, a->data, sizeI * sizeJ);
			}
		}
		else if (identifiedType == EArrayType::FLOAT)
		{
			MatrixData* ma = (MatrixData*)bd;

			//store in a temp float array then normalise
			if (normalise)
			{
				float* temp = new float[sizeI * sizeJ];

				//zero initialise
				for (size_t x = 0; x < sizeI * sizeJ; x++)
				{
					temp[x] = 0.0f;
				}

				add(temp, ma->data, sizeI * sizeJ);

				float m = maxValue(temp, sizeI * sizeJ);

				multiply(temp, 1 / m, sizeI * sizeJ);

				add(values, temp, sizeI * sizeJ);

				delete[] temp;
			}
			else
			{
				add(values, ma->data, sizeI * sizeJ);
			}
		}
	}

	//values are ready
	multiply(values, 1 / (float)accountLen, sizeI * sizeJ);
}

//writes the data to a file
void HeatmapReport::write(string fileName)
{
	ofstream file;
	string path = AM->getExecutableFolder() + "\\" + fileName + ".txt";

	file.open(path.c_str());

	if (!file.is_open())
	{
		//failed to save heat map report
		throw;
	}

	for (size_t i = 0; i < sizeI; i++)
	{
		for (size_t j = 0; j < sizeJ; j++)
		{
			file << to_string(values[i * sizeJ + j]) << '\t';
		}

		file << '\n';
	}

	file.close();
}

//add two arrays (float and int)
void HeatmapReport::add(float * base, int * additive, size_t size)
{
	//add each element pairwise
	for (size_t i = 0; i < size; i++)
	{
		base[i] += (float)additive[i];
	}
}

//add two arrays (double float)
void HeatmapReport::add(float * base, float * additive, size_t size)
{
	//add each element pairwise
	for (size_t i = 0; i < size; i++)
	{
		base[i] += additive[i];
	}
}

//multply array
void HeatmapReport::multiply(float * base, float multiplier, size_t size)
{
	//multply each number
	for (size_t i = 0; i < size; i++)
	{
		base[i] *= multiplier;
	}
}

//get the maximum value from an array
float HeatmapReport::maxValue(float * array, size_t size)
{
	float max = 0.0f;

	//multply each number
	for (size_t i = 0; i < size; i++)
	{
		//magnitude check
		if (abs(array[i]) > abs(max))
		{
			max = array[i];
		}
	}

	return max;
}
