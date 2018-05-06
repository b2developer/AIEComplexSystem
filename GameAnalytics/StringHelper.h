#pragma once
#include <string>
#include <vector>
#include "StringHelper.h"

#include "dllimport.h"

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
DLL_EXP vector<string> split(string data, char split);

/*
* find
*
* locates the first instance of the char 'key' in the
* string 'data' and returns its index in the string
*
* @param string data - the string to search
* @param char key - the char to search for
* @returns int - the index of the first instance (-1 if it doesn't exist)
*/
DLL_EXP int find(string data, char key);
