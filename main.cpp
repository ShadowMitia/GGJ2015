#include "Game.hpp"

#include <string.h>

int main(int argc, char* argv[]){
	bool startServer = false;
	for (int i = 0; i < argc; i++){
		std::cout << argv[i] << std::endl;
		if (strcmp(argv[i], "server") == 0){
			startServer = true;
		}
	}
	std::cout << startServer << std::endl;
	Game myGame("Toujours Plus!", startServer);
	myGame.run();

	return 0;
}