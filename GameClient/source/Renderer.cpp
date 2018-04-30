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
	screen /= 100.0f;

	vec2 size = vec2((dimensions.x * transform->scale.x) * screen.x, (dimensions.y * transform->scale.y) * screen.y);

	app2D->m_2dRenderer->drawSprite(texture, transform->position.x * screen.x + size.x * 0.5f, transform->position.y * screen.y + size.y * 0.5f, size.x , size.y, transform->rotation);
}