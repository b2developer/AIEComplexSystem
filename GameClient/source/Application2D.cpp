#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "GameAnalytics.h"
#include "Chef.h"

//constructor
Application2D::Application2D() 
{

}

//destructor
Application2D::~Application2D() 
{

}

//runs when the application is started, returns true if the application can begin the main loop
bool Application2D::startup() 
{
	GA->connect();
		
	Variable data = Variable();
	data.i = 5;

	GA->updateData("num2", data, EVariableType::INT);

	m_2dRenderer = new aie::Renderer2D();

	getExecutableFolder();

	string rootPath = executablePath;

	string addition = rootPath;
	addition += "/font/consolas.ttf";
	
	m_font = new aie::Font(addition.c_str(), 32);
	
	addition = rootPath;
	addition += "/textures/default.png";

	m_testTexture = new aie::Texture(addition.c_str());

	m_cameraX = 0;
	m_cameraY = 0;

	//initialise the object spawner
	Chef* chef = new Chef();
	chef->app2D = this;

	//create a test object
	GameObject* g = chef->cook(Recipe::Test);

	//create a game state
	state = new GameState();
	state->name = "main";
	state->gameObjects.push_back(g);

	return true;
}

//runs when the application is closed
void Application2D::shutdown() 
{
	delete state;

	delete m_font;
	delete m_2dRenderer;
}

//main update loop
void Application2D::update(float deltaTime) 
{
	//input example
	aie::Input* input = aie::Input::getInstance();

	state->update(deltaTime);
}

//main render loop
void Application2D::draw() 
{
	//wipe the screen to the background colour
	clearScreen();

	//set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	//begin drawing sprites
	m_2dRenderer->begin();

	state->render();

	//done drawing sprites
	m_2dRenderer->end();
}

void Application2D::getExecutableFolder()
{
	GetModuleFileName(NULL, executablePath, MAX_PATH);

	char *pos;
	if (pos = strrchr(executablePath, '\\'))
	{
		*pos = 0;
	}
}
