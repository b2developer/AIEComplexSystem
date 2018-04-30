#include "Chef.h"
#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "TextRenderer.h"
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
		r->texture = RL->m_testTexture;
		r->dimensions = vec2(100, 100);

		g->comps.push_back((Component*)r);
		
		r->initialise(g);

		return g;
	}

	return nullptr;
}
