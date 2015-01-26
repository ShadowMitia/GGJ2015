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

	void send(sf::Packet packet){
		status = server.send(packet);
	}

	void receive(sf::Packet packet, int info){
		if (info == 0){
			for (int i = 0; i < NUMBER_PLAYER; i++){
				for (int j = 0; j < MAX_RESSOURCES; j++){
					packet >> currentTurnRessources[i][j];
				}
			}
		}

	}


private:

	sf::TcpSocket server;
	sf::Socket::Status status;
	int gamePort;

	sf::TcpListener listener;
};

#endif