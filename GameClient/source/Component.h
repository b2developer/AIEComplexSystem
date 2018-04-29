#pragma once

//forward declaration
class Transform;
class GameObject;

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
public:

	//gameobject that owns this component
	GameObject * holder = nullptr;

	//transform component of the gameObject
	Transform* transform = nullptr;

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
	* initialise
	*
	* runs once when the object is created
	*
	* @param GameObject* - pointer to the gameObject holding this component
	* @returns void
	*/
	void initialise(GameObject* gameObject);
	
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