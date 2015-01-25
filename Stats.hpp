#ifndef HEADER_STATS
#define HEADER_STATS

#include "RessourceManager.hpp"

class Stats {
public:

	static void drawCurrentTurnRessources(sf::RenderTarget& target, RessourceManager& manager, int currentChief){
		const std::vector<std::vector<int>>& currentTurnRessources = manager.getCurrentTurnRessources();
		for (unsigned int i = 0; i < currentTurnRessources.size(); i++){
			for (unsigned int j = 0; j < currentTurnRessources[i].size(); j++){
				if (i == currentChief){
					break;
				}
				// @todo: print value name under bar, print player number under graph
				
				sf::RectangleShape temp(sf::Vector2f(50, currentTurnRessources[i][j] * 10));
				temp.setPosition((i * 200 - temp.getSize().x) + 60 * j + 100, 500 - (temp.getSize().y));
				sf::Color col(180, 50 * i, 75);
				temp.setFillColor(col);
				target.draw(temp);
			}
		}
	}

	static void drawCurrentTurnValuesRessources(sf::RenderTarget& target, RessourceManager& manager, int currentChief, int turn){
		const std::vector<std::vector<int>>& currentTurnRessources = manager.getCurrentTurnRessources();
		manager.calculateRessourceValueVariations(turn);
		const std::vector<std::vector<int>>& currentVariancesRessources = manager.getVariancesRessources();

		for (unsigned int i = 0; i < currentTurnRessources.size(); i++){
			int totJoueur = 0;
			if (i == currentChief){
					break;
			}
			for (unsigned int j = 0; j < currentTurnRessources[i].size(); j++){

				// @todo: print value name under bar, print player number under graph
				totJoueur += currentTurnRessources[i][j] * currentVariancesRessources[j][turn];
			}

			sf::RectangleShape temp(sf::Vector2f(50, totJoueur));
			temp.setPosition((i * 200 - temp.getSize().x), 500 - (temp.getSize().y));
			sf::Color col(180, 50 * i, 75);
			temp.setFillColor(col);
			target.draw(temp);
		}
	}

private:

};

#endif