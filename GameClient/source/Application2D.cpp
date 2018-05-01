#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "ResourceLibrary.h"
#include "GameAnalytics.h"
#include "Chef.h"

#include "IntData.h"
#include "FloatData.h"
#include "StringData.h"

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
	//initialise the resource library
	RL;

	if (!GA->connect())
	{
		return false;
	}
		
	IntData i = IntData();
	i.name = "asd";
	i.data = 5;

	GA->updateData(&i, EUpdate::OVERWRITE);

	b = new int*[4];

	for (int i = 0; i < 4; i++)
	{
		b[i] = new int[6];

		for (int j = 0; j < 6; j++)
		{
			b[i][j] = i * 6 + j;
		}
	}

	m_2dRenderer = new aie::Renderer2D();

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


