#ifndef HEADER_STORAGE
#define HEADER_STORAGE

#include <iostream>

static constexpr int MAX_RESSOURCES = 4;
static constexpr int NUMBER_PLAYER = 4;


class RessourceManager {
public:
	RessourceManager() : currentTurnRessources(NUMBER_PLAYER), globalRessources(NUMBER_PLAYER), variancesRessources(MAX_RESSOURCES){
		for (unsigned int i = 0; i < NUMBER_PLAYER; i++){
			for (unsigned int j = 0; j < MAX_RESSOURCES; j++){
				currentTurnRessources[i].push_back(0);
				globalRessources[i].push_back(0);
			}
		}

		for (unsigned int i = 0; i < MAX_RESSOURCES; i++){
			variancesRessources[i].push_back(0);
		}

		printDebug();

	}

	static void printMatrix(std::vector<std::vector<int>> m){
		for (unsigned int i = 0; i < m.size(); i++){
			for (unsigned int j = 0; j < m[i].size(); j++){
				std::cout << m[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	void printDebug(){
		//printMatrix(currentTurnRessources);
		//std::cout << std::endl << std::endl;

		printMatrix(globalRessources);
		std::cout << std::endl << std::endl;

		//printMatrix(variancesRessources);
		//std::cout << std::endl;
	}

	void playerGrabRessource(Player& player, int type){
		globalRessources[player.getNumber()][type]++;
	}

private:

	std::vector<std::vector<int>> currentTurnRessources;
	std::vector<std::vector<int>> globalRessources;
	std::vector<std::vector<int>> variancesRessources;
};

#endif