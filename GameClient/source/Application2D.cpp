#include "Application2D.h"
#include <time.h>

#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "ResourceLibrary.h"
#include "GameAnalytics.h"
#include "Chef.h"

#include "Button.h"
#include "TextRenderer.h"

#include "IntData.h"
#include "FloatData.h"
#include "StringData.h"
#include "ArrayData.h"
#include "MatrixData.h"

//call-backs of the pressed buttons
void onButtonPressed1()
{
	IntData i = IntData();
	i.name = "num1";
	i.data = 1;

	GA->updateData(&i, EUpdate::OFFSET);
}

void onButtonPressed2()
{
	FloatData f = FloatData();
	f.name = "num2";
	f.data = 1.0f;

	GA->updateData(&f, EUpdate::OFFSET);
}

void onButtonPressed3()
{
	IntData i = IntData();
	i.name = "num3";
	i.data = 1;

	GA->updateData(&i, EUpdate::OFFSET);
}


//constructor
Application2D::Application2D() 
{

}

//destructor
Application2D::~Application2D() 
{
	delete state;
	delete m_2dRenderer;
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
		
	srand((unsigned int)time(NULL));

	IntData i = IntData();
	i.name = "num1";
	i.data = 1;

	GA->updateData(&i, EUpdate::OVERWRITE);

	FloatData f = FloatData();
	f.name = "num2";
	f.data = 1;

	GA->updateData(&i, EUpdate::OVERWRITE);

	IntData i2 = IntData();
	i2.name = "num3";
	i2.data = 1;

	GA->updateData(&i2, EUpdate::OVERWRITE);

	FloatData f2 = FloatData();
	f2.name = "time";
	f2.data = 0.0f;

	GA->updateData(&f2, EUpdate::OVERWRITE);

	int* b = new int[16];

	for (int i = 0; i < 16; i++)
	{
		b[i] = i;
	}

	ArrayData a = ArrayData();
	a.name = "array";
	a.sizeI = 4;
	a.sizeJ = 4;
	a.data = b;

	GA->updateData(&a, EUpdate::OVERWRITE);

	float* c = new float[49];

	for (int i = 0; i < 49; i++)
	{
		c[i] = i * 20.0f;
	}

	MatrixData d = MatrixData();
	d.name = "matrix";
	d.sizeI = 7;
	d.sizeJ = 7;
	d.data = c;

	GA->updateData(&d, EUpdate::OVERWRITE);

	m_2dRenderer = new aie::Renderer2D();

	m_cameraX = 0;
	m_cameraY = 0;

	//initialise the object spawner
	Chef* chef = new Chef();
	chef->app2D = this;

	//create a test object
	GameObject* g = chef->cook(Recipe::Test);
	GameObject* b1 = chef->cook(Recipe::Button);
	GameObject* b2 = chef->cook(Recipe::Button);
	GameObject* b3 = chef->cook(Recipe::Button);

	b2->comps[1]->transform->position.x = 25.0f;
	b3->comps[1]->transform->position.x = 50.0f;

	b1->getComponentOfType<ButtonC>()->onPressed = &onButtonPressed1;
	b2->getComponentOfType<ButtonC>()->onPressed = &onButtonPressed2;
	b3->getComponentOfType<ButtonC>()->onPressed = &onButtonPressed3;

	b1->getComponentOfType<TextRenderer>()->text = "Button1";
	b2->getComponentOfType<TextRenderer>()->text = "Button2";
	b3->getComponentOfType<TextRenderer>()->text = "Button3";

	//create a game state
	state = new GameState();
	state->name = "main";
	state->gameObjects.push_back(g);
	state->gameObjects.push_back(b1);
	state->gameObjects.push_back(b2);
	state->gameObjects.push_back(b3);

	return true;
}

//runs when the application is closed
void Application2D::shutdown() 
{
	
}

//main update loop
void Application2D::update(float deltaTime) 
{
	//input example
	aie::Input* input = aie::Input::getInstance();

	FloatData f = FloatData();
	f.name = "time";
	f.data = deltaTime;

	GA->updateData(&f, EUpdate::OFFSET);

	int* b = new int[16];

	for (int i = 0; i < 16; i++)
	{
		b[i] = 1;
	}

	ArrayData a = ArrayData();
	a.name = "array";
	a.sizeI = 4;
	a.sizeJ = 4;
	a.data = b;

	GA->updateData(&a, EUpdate::OFFSET);

	state->update(deltaTime);

	//shutdown the app if connection is lost
	if (!GA->connected)
	{
		quit();
	}
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



