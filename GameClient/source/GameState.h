#pragma once
#include <string>
#include <vector>

using namespace std;

//forward declaration
class GameObject;

/*
* class GameState
*
* manages a collection of gameobjects and communicates transitions
* to other gamestates in a stack like structure
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018
*/
class GameState
{
public:

	string name;

	//name of the gamestate that called this
	string origin;

	vector<GameObject*> gameObjects;

	/*
	* GameState()
	* default constructor
	*/
	GameState();

	/*
	* ~GameState()
	* destructor, removes gameobjects
	*/
	~GameState();

	/*
	* update
	* 
	* gamestate loop function, updates all gameobjects
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