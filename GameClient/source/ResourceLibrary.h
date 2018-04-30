#pragma once
#include <string>
#include <Windows.h>

#include "Texture.h"
#include "Font.h"

using namespace std;

#define RL ResourceLibrary::getInstance()

/*
* class ResourceLibrary
*
* singleton that holds all loaded textures,
* the .exe folder directory and other important resources
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018
*/
class ResourceLibrary
{
private:

	/*
	* ResourceLibrary()
	* constructor, loads resources
	*/
	ResourceLibrary();

	/*
	* ~ResourceLibrary()
	* destructors, unloads resources
	*/
	~ResourceLibrary();

public:

	char executablePath[MAX_PATH];

	//resources
	aie::Font* m_font;
	aie::Texture* m_testTexture;

	/*
	* getInstance
	*
	* gets a pointer to the only instance of the game analytics object,
	* creates the object if it doesn't already exist
	*
	* @returns static ResourceLibrary* - pointer to the singleton
	*/
	static ResourceLibrary* getInstance();


	/*
	* getExecutableFolder
	*
	* gets the path that the .exe running from resides in
	*
	* @returns void
	*/
	void getExecutableFolder();
};