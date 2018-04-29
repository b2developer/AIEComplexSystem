#include "Renderer.h"
#include "Transform.h"
#include "Application2D.h"

//constructor
Renderer::Renderer(Application2D * _app2D)
{
	app2D = _app2D;
}

//render loop
void Renderer::render()
{
	vec2 screen = vec2(app2D->getWindowWidth(), app2D->getWindowHeight());
	screen /= 50.0f;

	app2D->m_2dRenderer->drawSprite(texture, transform->position.x * screen.x, transform->position.y * screen.y, (dimensions.x * transform->scale.x) * screen.x, (dimensions.y * transform->scale.y) * screen.y, transform->rotation);
}