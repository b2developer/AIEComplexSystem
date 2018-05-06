#include "Chef.h"
#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "TextRenderer.h"
#include "Button.h"
#include "Application2D.h"

#include "ResourceLibrary.h"

//generation function
GameObject * Chef::cook(Recipe recipe)
{
	if (recipe == Recipe::Test)
	{
		GameObject* g = new GameObject();

		Transform* t = new Transform();
		g->comps.push_back((Component*)t);

		Renderer* r = new Renderer(app2D);
		r->texture = RL->m_red;
		r->dimensions = vec2(100, 100);

		g->comps.push_back((Component*)r);
		
		r->initialise(g);

		return g;
	}
	else if (recipe == Recipe::Button)
	{
		GameObject* g = new GameObject();

		Transform* t = new Transform();
		g->comps.push_back((Component*)t);

		Renderer* r = new Renderer(app2D);
		
		r->texture = RL->m_blue;
		r->dimensions = vec2(20, 20);

		TextRenderer* tr = new TextRenderer(app2D);

		tr->font = RL->m_font;

		ButtonC* b = new ButtonC(app2D);

		b->min = vec2(0, 0);
		b->max = vec2(20, 20);

		g->comps.push_back((Component*)r);
		g->comps.push_back((ButtonC*)b);
		g->comps.push_back((TextRenderer*)tr);

		r->initialise(g);
		b->initialise(g);
		tr->initialise(g);

		return g;
	}

	return nullptr;
}
