#pragma once
#include "Component.h"
#include <glm/common.hpp>
#include <Texture.h>

using namespace glm;

//forward declaration
class Application2D;

/*
* class ButtonC
* child class of Component
*
* a component that creates a collidable region
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018
*/
class ButtonC : public Component
{
public:

	bool prevMouse = false;

	vec2 min, max;

	Application2D* appPtr = nullptr;

	void (*onPressed)() = nullptr;

	/*
	* ButtonC(Application2D* appPtr)
	* constructor, gives the application pointer
	*
	* @param Application2D* _appPtr - gives the screen width
	*/
	ButtonC(Application2D* _appPtr);

	/*
	* ~ButtonC()
	* virtual function
	* default destructor
	*/
	virtual ~ButtonC() {}

	/*
	* update
	* overrides Component's update(float deltaTime)
	*
	* game update loop
	*
	* @param float deltaTime - the amount of time passed since the last frame
	* @returns void
	*/
	virtual void update(float deltaTime) override;

	/*
	* render
	* overrides Component's render()
	*
	* graphical function loop
	*
	* @returns void
	*/
	virtual void render() override {};

};