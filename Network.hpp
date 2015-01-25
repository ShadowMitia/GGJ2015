#ifndef HEADER_NETWORK
#define HEADER_NETWORK

class Network {
public:
	Network(sf::IpAddress address, int port) : server(){
		gamePort = port;
		status = server.connect(address, gamePort);
		if (status != sf::Socket::Done){
			std::cout << "Problem establishing link with " << address << std::endl;
		}
		std::cout << "Connected to server " << address << std::endl;

		/*
		 // Receive a message from the server
		char in[128];
		std::size_t received;
		if (server.receive(in, sizeof(in), received) != sf::Socket::Done)
		return;
		std::cout << "Message received from the server: \"" << in << "\"" << std::endl;
		// Send an answer to the server
		const char out[] = "Hi, I'm a client";
		if (server.send(out, sizeof(out)) != sf::Socket::Done)
		return;
		std::cout << "Message sent to the server: \"" << out << "\"" << std::endl;
		*/

	}

	Network(int port){

		if (listener.listen(port) != sf::Socket::Done) {
			std::cout << "[SERVER]Couldn't create listener on port: " << port << std::endl;
		}
		std::cout << "Server is listening to port " << port << ", waiting for connections... " << std::endl;

		sf::TcpSocket server;
		if (listener.accept(server) != sf::Socket::Done){
			std::cout << "[SERVER]Couldn't accept client " << std::endl;
		}
		std::cout << "Client connected: " << server.getRemoteAddress() << std::endl;
	}


private:

	sf::TcpSocket server;
	sf::Socket::Status status;
	int gamePort;

	sf::TcpListener listener;
};

#endif