#pragma once

/*
* class Component
*
* a piece of a gameobject that adds functionality to it
* eg. rendering, transform, collisions
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018
*/
class Component
{
protected:

	/*
	* Component()
	* default constructor
	*/
	Component() {}

	/*
	* ~Component()
	* virtual function
	* default destructor
	*/
	virtual ~Component() {}

	/*
	* update
	* abstract function
	*
	* game update loop
	*
	* @param float deltaTime - the amount of time passed since the last frame
	* @returns void 
	*/
	virtual void update(float deltaTime) = 0;

	/*
	* render
	* abstract function
	*
	* graphical function loop
	*
	* @returns void
	*/
	virtual void render() = 0;

};