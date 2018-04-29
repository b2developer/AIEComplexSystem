#pragma once
#include "Component.h"
#include <glm/common.hpp>
#include <Texture.h>

using namespace glm;
using namespace aie;

//forward declaration
class Application2D;

/*
* class Renderer
* child class of Component
*
* a component that renders a texture to a specific position
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018
*/
class Renderer : public Component
{
public:

	//pointer to the texture to use
	Texture * texture = nullptr;

	//size of the rendered texture
	vec2 dimensions = vec2(0, 0);

	//object that renders the texture
	Application2D* app2D = nullptr;

	/*
	* Renderer()
	* constructor, gives the renderer component the 2D graphical renderer
	*
	* @param Application2D* _app2D - the 2D graphical renderer
	*/
	Renderer(Application2D* _app2D);

	/*
	* ~Renderer()
	* virtual function
	* default destructor
	*/
	virtual ~Renderer() {}

	/*
	* update
	* overrides Component's update(float deltaTime)
	*
	* game update loop
	*
	* @param float deltaTime - the amount of time passed since the last frame
	* @returns void
	*/
	virtual void update(float deltaTime) override {};

	/*
	* render
	* overrides Component's render()
	*
	* graphical function loop
	*
	* @returns void
	*/
	virtual void render() override;

};