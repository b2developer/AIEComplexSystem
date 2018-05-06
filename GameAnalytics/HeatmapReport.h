#pragma once
#include <vector>
#include <string>
#include "dllimport.h"

using namespace std;

/*
* class HeatmapReport
*
* data analysis for 2D arrays of data, adds each array up and normalises it,
* granting some insight about positional/spatial patterns
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018
*/
class HeatmapReport
{
public:

	size_t sizeI;
	size_t sizeJ;
	
	//array of values
	float* values;

	/*
	* HeatmapReport()
	* default constructor
	*/
	DLL_EXP HeatmapReport() {};

	/*
	* ~HeatmapReport()
	* destructor, deallocates array
	*/
	DLL_EXP ~HeatmapReport();

	/*
	* initialise
	*
	* grabs all 2d arrays and combines them into one averaged array
	*
	* @param string table - the name of the table
	* @param bool normalise - normalise all input arrays before inserting them
	* @returns void
	*/
	DLL_EXP void initialise(string table, bool normalise = false);

	/*
	* write
	*
	* copies the contents of the report to a text file
	*
	* @param string fileName - the name of the file to write to
	* @returns void
	*/
	DLL_EXP void write(string fileName);

private:

	/*
	* add
	*
	* adds two arrays together
	*
	* @param int* base - the array to add to
	* @param int* additive - the array to add from
	* @param size_t size - the length of both arrays
	* @returns void
	*/
	DLL_EXP void add(float* base, int* additive, size_t size);

	/*
	* add
	*
	* adds two arrays together
	*
	* @param float* base - the array to add to
	* @param float* additive - the array to add from
	* @param size_t size - the length of both arrays
	* @returns void
	*/
	DLL_EXP void add(float* base, float* additive, size_t size);

	/*
	* multiply
	*
	* multiplies an array by a number
	*
	* @param float* base - the array to multiply
	* @param float multiplier - the number to multiply the array by
	* @param size_t size - the length of the array
	* @returns void
	*/
	DLL_EXP void multiply(float* base, float multiplier, size_t size);

	/*
	* maxValue
	*
	* gets the maximum value of the array
	*
	* @param float* array - the array to search
	* @param size_t size - the length of the array
	* @returns float - the maximum value
	*/
	DLL_EXP float maxValue(float* array, size_t size);

};