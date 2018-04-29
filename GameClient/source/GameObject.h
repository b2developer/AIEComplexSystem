#pragma once
#include <vector>
#include "Transform.h"

#define TEMPLATE template<typename T>

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

	/*
	* getComponentOfType
	* template function
	*
	* searches for a component of a specific type 
	* that is being held by this gameobject
	*
	* @returns T* - pointer to the found type or nullptr if no matching object is found
	*/
	TEMPLATE
	T * getComponentOfType()
	{
		size_t compSize = comps.size();

		//render all components
		for (size_t i = 0; i < compSize; i++)
		{
			T* test = dynamic_cast<T*>(comps[i]);

			//type match test
			if (test != nullptr)
			{
				return test;
			}
		}

		return nullptr;
	}

};

