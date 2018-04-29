#pragma once
#include <Windows.h>
#include "Application.h"
#include "Renderer2D.h"
#include "GameState.h"
#include "GameObject.h"

/*
* class Application2D
* child class of aie::Application
*
* controls the game's update and rendering loops
* 
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018
*/
class Application2D : public aie::Application 
{
public:

	/*
	* Application2D()
	* default constructor
	*/
	Application2D();

	/*
	* ~Application2D()
	* virtual function
	* default destructor
	*/
	virtual ~Application2D();

	/*
	* startup
	* virtual function
	*
	* runs once when application is created and initialises resources and managers
	*
	* @returns bool - flag indicating if the application started correctly
	*/
	virtual bool startup();

	/*
	* shutdown
	* virtual function
	*
	* runs when the application is destroyed and deallocates resources and managers
	*
	* @returns void
	*/
	virtual void shutdown();

	/*
	* update
	* virtual function
	*
	* main game logic loop, updates all entities and managers
	*
	* @param deltaTime - the amount of time passed since the last frame
	* @returns void
	*/
	virtual void update(float deltaTime);

	/*
	* draw
	* virtual function
	*
	* rendering loop, renders all graphical components
	*
	* @returns void
	*/
	virtual void draw();

	/*
	* getExecutableFolder
	*
	* gets the path of the /bin folder
	*
	* @returns void
	*/
	void getExecutableFolder();

	char executablePath[MAX_PATH];

	GameState* state;

	aie::Renderer2D*	m_2dRenderer;

	aie::Font*			m_font;
	aie::Texture*		m_testTexture;

protected:

	float m_cameraX, m_cameraY;
};