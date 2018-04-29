#include "TextRenderer.h"
#include "Transform.h"
#include "Application2D.h"

//constructor
TextRenderer::TextRenderer(Application2D * _app2D)
{
	app2D = _app2D;
}

//render loop
void TextRenderer::render()
{
	vec2 screen = vec2(app2D->getWindowWidth(), app2D->getWindowHeight());
	screen /= 50.0f;

	app2D->m_2dRenderer->drawText(font, text.c_str(), transform->position.x * screen.x, transform->position.y * screen.y);
}
