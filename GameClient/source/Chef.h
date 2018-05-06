#pragma once

//forward declaration
class GameObject;
class Application2D;

enum Recipe
{
	Test,
	Button,
};

/*
* class Chef
*
* creates GameObjects by generating the necessary components with the required pointers
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018
*/
class Chef
{
public:

	Application2D* app2D;

	/*
	* Chef()
	* default constructor
	*/
	Chef() {}

	/*
	* ~Chef()
	* default destructor
	*/
	~Chef() {}
	
	/*
	* cook
	*
	* creates a GameObject with neccessarycomponents based on the recipe
	*
	* @param Recipe recipe - type of GameObject to create
	* @returns GameObject* - pointer to the generated GameObject
	*/
	GameObject* cook(Recipe recipe);
};