#include "Application2D.h"
#include "GameAnalytics.h"

int main() 
{

	// allocation
	auto app = new Application2D();

	//the game only runs if the game analytics system can connect
	if (GA->connect())
	{
		// initialise and loop
		app->run("GameClient", 1280, 720, false);
	}

	// deallocation
	delete app;

	return 0;
}