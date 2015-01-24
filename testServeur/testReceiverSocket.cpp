#include <iostream>
#include <string>
#include <SFML/Network.hpp>

int main(int argc, char* argv[]) {
	sf::UdpSocket socket;
	socket.bind(54001);

	sf::Packet receivingPacket;
	sf::IpAddress sender;
	unsigned short port;

	std::cout << "Receiving..." << std::endl;
	std::string message;
	while (message.size() < 10){
		socket.receive(receivingPacket, sender, port);
		receivingPacket >> message;
	}
	std::cout << "Message: " << message << " from: " << sender.toString() << std::endl;;
	

	return 0;
}