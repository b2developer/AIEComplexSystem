#pragma once
#include "Component.h"
#include <glm/common.hpp>

using namespace glm;

/*
* class Transform
* child class of Component
*
* a component that records a position, rotation and relative scale
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018
*/
class Transform : public Component
{
public:

	//transform variables
	vec2 position = vec2(0,0);
	float rotation = 0.0f; //radians
	vec2 scale = vec2(1,1);

	/*
	* Transform()
	* default constructor
	*/
	Transform() {}

	/*
	* ~Transform()
	* virtual function
	* default destructor
	*/
	virtual ~Transform() {}

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
	virtual void render() override {};

};