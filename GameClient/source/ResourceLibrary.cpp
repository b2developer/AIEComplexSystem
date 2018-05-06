#include "ResourceLibrary.h"

//loads resources
ResourceLibrary::ResourceLibrary()
{
	getExecutableFolder();

	string rootPath = executablePath;

	//------------

	string addition = rootPath;
	addition += "/font/consolas.ttf";

	m_font = new aie::Font(addition.c_str(), 32);

	//------------

	addition = rootPath;
	addition += "/textures/blue.png";

	m_blue = new aie::Texture(addition.c_str());

	//------------

	addition = rootPath;
	addition += "/textures/red.png";

	m_red = new aie::Texture(addition.c_str());

	//------------
}

//unloads resources
ResourceLibrary::~ResourceLibrary()
{
	delete m_font;
	delete m_blue;
	delete m_red;
}

//singleton instance retrieval
ResourceLibrary * ResourceLibrary::getInstance()
{
	static ResourceLibrary* singleton = nullptr;

	//create the singleton if it doesn't exist already
	if (singleton == nullptr)
	{
		singleton = new ResourceLibrary();
	}

	return singleton;
}

//gets the directory that the .exe is stored in
void ResourceLibrary::getExecutableFolder()
{
	GetModuleFileName(NULL, executablePath, MAX_PATH);

	char *pos;
	if (pos = strrchr(executablePath, '\\'))
	{
		*pos = 0;
	}
}