#include <iostream>
#include <string>

#include <SFML/Network.hpp>

int main(int argc, char* argv[]) {
	/*
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
	std::cout << "Message: " << message << " from: " << sender.toString() << std::endl;
	*/
	std::cout << "COUCOU" << std::endl;

	sf::TcpListener listener;

	std::cout << "RE" << std::endl;
	if (listener.listen(53000) != sf::Socket::Done) {
		std::cout << "[SERVER]Couldn't create listener on port: " << 53000 << std::endl;
	}
	std::cout << "Server is listening to port " << 53000 << ", waiting for connections... " << std::endl;

	sf::TcpSocket client;
	if (listener.accept(client) != sf::Socket::Done){
		std::cout << "[SERVER]Couldn't accept client " << std::endl;
	}
	std::cout << "Client connected: " << client.getRemoteAddress() << std::endl;


	// Send a message to the connected client
	const char out[] = "Hi, I'm the server";
	if (client.send(out, sizeof(out)) != sf::Socket::Done)
	return 1;
	std::cout << "Message sent to the client: \"" << out << "\"" << std::endl;
	// Receive a message back from the client
	char in[128];
	std::size_t received;
	if (client.receive(in, sizeof(in), received) != sf::Socket::Done)
	return 1;
	std::cout << "Answer received from the client: \"" << in << "\"" << std::endl;

	return 0;
}