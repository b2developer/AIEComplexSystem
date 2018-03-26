#include "Application2D.h"
#include "testObject.h"

int main() 
{

	TestObject* to = new TestObject();
	to->add();
	
	// allocation
	auto app = new Application2D();

	// initialise and loop
	app->run("GameClient", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}