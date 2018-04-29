#include "GameState.h"
#include "GameObject.h"

//constructor
GameState::GameState()
{

}

//destructor
GameState::~GameState()
{
	size_t objSize = gameObjects.size();

	//update all gameobjects
	for (size_t i = 0; i < objSize; i++)
	{
		delete gameObjects[i];
	}
}

//update loop
void GameState::update(float deltaTime)
{
	size_t objSize = gameObjects.size();

	//update all gameobjects
	for (size_t i = 0; i < objSize; i++)
	{
		gameObjects[i]->update(deltaTime);
	}
}

//render loop
void GameState::render()
{
	size_t objSize = gameObjects.size();

	//render all gameobjects
	for (size_t i = 0; i < objSize; i++)
	{
		gameObjects[i]->render();
	}
}
