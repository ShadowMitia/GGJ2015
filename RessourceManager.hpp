#ifndef HEADER_STORAGE
#define HEADER_STORAGE

#include <iostream>

static constexpr int MAX_RESSOURCES = 4;
static constexpr int NUMBER_PLAYER = 4;


class RessourceManager {
public:
	RessourceManager() : currentTurnRessources(NUMBER_PLAYER), currentTurnChiefRessources(NUMBER_PLAYER), globalRessources(NUMBER_PLAYER), variancesRessources(MAX_RESSOURCES){
		for (unsigned int i = 0; i < NUMBER_PLAYER; i++){
			for (unsigned int j = 0; j < MAX_RESSOURCES; j++){
				currentTurnRessources[i].push_back(0);
				currentTurnChiefRessources[i].push_back(0);
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
		printMatrix(currentTurnRessources);
		std::cout << std::endl << std::endl;

		printMatrix(currentTurnChiefRessources);
		std::cout << std::endl << std::endl;

		printMatrix(globalRessources);
		std::cout << std::endl << std::endl;

		printMatrix(variancesRessources);
		std::cout << std::endl;
	}

	void playerGrabRessource(Player& player, int type){
		currentTurnRessources[player.getNumber()][type]++;
	}

	void addCurrentTurnToGlobal(){
		for (unsigned int i = 0; i < currentTurnRessources.size(); i++){
			for (unsigned int j = 0; j < currentTurnRessources[i].size(); j++){
				globalRessources[i][j] += currentTurnRessources[i][j];
			}
		}
	}

	float getChiefEfficiency() { return chiefEfficiency; }
	std::vector<std::vector<int>> getCurrentTurnRessources() { return currentTurnRessources; }
	std::vector<std::vector<int>> getCurrentTurnChiefRessources() { return currentTurnChiefRessources; }
	std::vector<std::vector<int>> getGlobalRessources() { return globalRessources; }
	std::vector<std::vector<int>> getVariancesRessources() { return variancesRessources; }

	void calculateChiefEfficiency(int currentTurn) {
		float sumCurrentTurnRessourcesVariances = 0;
		float sumChiefsTurnRessourcesVariances = 0;
		for (unsigned int i = 0; i < currentTurnRessources.size(); i++){
			for (unsigned int j = 0; j < currentTurnRessources[i].size(); j++) {
				sumCurrentTurnRessourcesVariances += currentTurnRessources[i][j] * variancesRessources[i][currentTurn];
				sumChiefsTurnRessourcesVariances += currentTurnChiefRessources[i][j] * variancesRessources[i][currentTurn];
			}
		}

		float temp = (1 - std::abs( sumCurrentTurnRessourcesVariances - sumChiefsTurnRessourcesVariances) / sumCurrentTurnRessourcesVariances);
		chiefEfficiency = temp > 0 ? temp : 0;
	}

	void calculateRessourceValueVariations(int currentTurn){
		int total = 0;
		for (unsigned int i = 0; i < currentTurnRessources.size(); i++){
			for (unsigned int j = 0; j < currentTurnRessources[i].size(); j++){
				total += currentTurnRessources[i][j];
			}
		}

		float sumGatheredRessources = 0;
		float sumChiefsRessources = 0;

		for (unsigned int i = 0; i < currentTurnRessources.size(); i++){
			for (unsigned int j = 0; j < currentTurnRessources[i].size(); j++){
				sumGatheredRessources += currentTurnRessources[i][j] * variancesRessources[i][currentTurn];
				sumChiefsRessources += currentTurnChiefRessources[i][j] * variancesRessources[i][currentTurn];
			}
		}

		for (unsigned int i = 0; i < MAX_RESSOURCES; i++){
			int sum = 0;
			for (unsigned int j = 0; j < variancesRessources[i].size(); j++){
				sum += variancesRessources[i][j];
			}
			variancesRessources[i][currentTurn] += 1.5 - (sumGatheredRessources/total + sum / sumGatheredRessources );
		}
	}

private:

	std::vector<std::vector<int>> currentTurnRessources;
	std::vector<std::vector<int>> currentTurnChiefRessources;
	std::vector<std::vector<int>> globalRessources;
	std::vector<std::vector<int>> variancesRessources;

	float chiefEfficiency{1};
};

#endif