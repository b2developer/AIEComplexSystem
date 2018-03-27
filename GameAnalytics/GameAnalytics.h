#pragma once
#include "dllimport.h"

#define GA GameAnalytics::getInstance()

/*
* class GameAnalytics
*
* singleton that initialises various components required
* to communicate with the game analytics server, and track
* required data
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018
*/
class GameAnalytics
{
private:

	/*
	* GameAnalytics()
	* default constructor
	*/
	DLL_EXP GameAnalytics();

	/*
	* ~GameAnalytics()
	* default destructor
	*/
	DLL_EXP ~GameAnalytics();

public:

	/*
	* getInstance
	*
	* gets a pointer to the only instance of the game analytics object,
	* creates the object if it doesn't already exist
	*
	* @returns static GameAnalytics* - pointer to the singleton
	*/
	DLL_EXP static GameAnalytics* getInstance();
};