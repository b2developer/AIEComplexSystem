#include "GameObject.h"
#include "Component.h"

//constructor
GameObject::GameObject()
{
}

//destructor
GameObject::~GameObject()
{
	size_t compSize = comps.size();

	//delete all components
	for (size_t i = 0; i < compSize; i++)
	{
		delete comps[i];
	}
}

//update loop
void GameObject::update(float deltaTime)
{
	size_t compSize = comps.size();

	//update all components
	for (size_t i = 0; i < compSize; i++)
	{
		comps[i]->update(deltaTime);
	}
}

//render loop
void GameObject::render()
{
	size_t compSize = comps.size();

	//render all components
	for (size_t i = 0; i < compSize; i++)
	{
		comps[i]->render();
	}
}