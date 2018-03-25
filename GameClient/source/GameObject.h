#pragma once
#include <vector>

using namespace std;

//forward declaration
class Component;

/*
* class GameObject
*
* an entity that resides in a gamestate, can be updated, drawn
* and have it's functionality extended by adding components
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018
*/
class GameObject
{
public:

	//list of components
	vector<Component*> comps;

	/*
	* GameObject()
	* default constructor
	*/
	GameObject();

	/*
	* ~GameObject()
	* default destructor
	*/
	~GameObject();

	/*
	* update
	*
	* game logic function loop
	*
	* @param float deltaTime - the amount of time passed since the last frame
	* @returns void
	*/
	void update(float deltaTime);

	/*
	* render
	*
	* graphical function loop
	*
	* @returns void
	*/
	void render();

};