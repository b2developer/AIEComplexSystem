#include <iostream>
#include <string>

#include <SFML\Network.hpp>

using namespace sf;

//GameAnalytics

int main()
{

	TcpSocket socket;
	Socket::Status status = socket.connect("10.10.0.128", 5000);

	if (status != Socket::Done)
	{
		throw;
		//error
	}

	char data[100] = "My name is Barry Allen, and I'm the fastest man alive.";

	socket.send(data, 100);

	std::cout << "Success";

	return 0;
}