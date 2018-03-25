#include <iostream>
#include <string>

#include <SFML\Network.hpp>

using namespace sf;

//Server

int main()
{
	TcpListener listener;

	if (listener.listen(5000) != Socket::Done)
	{
		//error
	}

	while (true)
	{
		TcpSocket client;

		if (listener.accept(client) != Socket::Done)
		{
			//error
			continue;
		}

		break;
	}

	std::cout << "Success";

	return 0;
}