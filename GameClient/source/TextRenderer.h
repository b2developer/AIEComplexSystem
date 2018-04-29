#pragma once
#include "Component.h"
#include <glm/common.hpp>
#include <string>
#include <Font.h>

using namespace glm;
using namespace std;
using namespace aie;

//forward declaration
class Application2D;

/*
* class TextRenderer
* child class of Component
*
* a component that renders text to a position
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018
*/
class TextRenderer : public Component
{
public:

	//pointer to the font to use
	Font * font = nullptr;

	//size of the rendered texture
	vec2 dimensions = vec2(0, 0);

	string text;

	//object that renders the texture
	Application2D* app2D = nullptr;

	/*
	* TextRenderer()
	* constructor, gives the renderer component the 2D graphical renderer
	*
	* @param Application2D* _app2D - the 2D graphical renderer
	*/
	TextRenderer(Application2D* _app2D);

	/*
	* ~TextRenderer()
	* virtual function
	* default destructor
	*/
	virtual ~TextRenderer() {}

	/*
	* update
	* overrides Component's update(float deltaTime)
	*
	* game update loop
	*
	* @param float deltaTime - the amount of time passed since the last frame
	* @returns void
	*/
	virtual void update(float deltaTime) override {};

	/*
	* render
	* overrides Component's render()
	*
	* graphical function loop
	*
	* @returns void
	*/
	virtual void render() override;

};