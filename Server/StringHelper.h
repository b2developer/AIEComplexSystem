#pragma once
#include <string>
#include <vector>
#include "StringHelper.h"

using namespace std;

/*
* split
*
* returns an array of sub-strings which represent
* the original spring split by a specific char
*
* @param string data - the string to check
* @param char split - the char used to split the data
*
* @returns vector<string> - a list of sub-strings 
*/
vector<string> split(string data, char split);
