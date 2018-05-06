#include "Button.h"
#include "Application2D.h"
#include "Input.h"

#include <iostream>

//constructor
ButtonC::ButtonC(Application2D * _appPtr)
{
	appPtr = _appPtr;
}

//update loop
void ButtonC::update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	vec2 screen = vec2(appPtr->getWindowWidth(), appPtr->getWindowHeight());
	screen /= 100.0f;

	//get the position of the mouse
	vec2 mouse = vec2(input->getMouseX(), input->getMouseY());

	mouse.x /= screen.x;
	mouse.y /= screen.y;

	mouse -= transform->position;

	bool pressed = input->isMouseButtonDown(0);

	//is the button being pressed
	if (pressed && !prevMouse)
	{
		bool xCheck = min.x < mouse.x && max.x > mouse.x;
		bool yCheck = min.y < mouse.y && max.y > mouse.y;

		if (xCheck && yCheck)
		{
			std::cout << "Button Pressed.\n";
			onPressed();
		}
	}

	prevMouse = pressed;
}
