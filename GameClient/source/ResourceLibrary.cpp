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
	addition += "/textures/testTexture.png";

	m_testTexture = new aie::Texture(addition.c_str());

	//------------
}

//unloads resources
ResourceLibrary::~ResourceLibrary()
{
	delete m_font;
	delete m_testTexture;
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