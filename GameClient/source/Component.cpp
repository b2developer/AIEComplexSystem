#include "Component.h"
#include "GameObject.h"

//initialisation function
void Component::initialise(GameObject* gameObject)
{
	holder = gameObject;
	transform = holder->getComponentOfType<Transform>();
}
