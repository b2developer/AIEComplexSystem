#pragma once
#include "Component.h"
#include <glm/common.hpp>
#include <Texture.h>

using namespace glm;
using namespace aie;

/*
* class Renderer
* child class of Component
*
* a component that records a position, rotation and relative scale
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018
*/
class Renderer : Component
{
public:

	//pointer to the texture to use
	Texture * texture = nullptr;

	//size of the rendered texture
	vec2 dimensions = vec2(0, 0);

	/*
	* Renderer()
	* default constructor
	*/
	Renderer() {}

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