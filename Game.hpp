#ifndef HEADER_GAME
#define HEADER_GAME

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <vector>
#include <sstream>

#include "Player.hpp"
#include "Ressource.hpp"
#include "Collision.hpp"
#include "Powerup.hpp"
#include "RessourceManager.hpp"
#include "Stats.hpp"
#include "Network.hpp"

// For random things
#include <ctime>
#include <cstdlib>


const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60.f);

class Game : private sf::NonCopyable {
	public:
		Game(std::string name, bool server);
		void run();

	private:
		void processEvents();
		void update(sf::Time elapsedTime);
		void render();

		void updateStatistics(sf::Time elapsedTime);
		

	private:

		// General game things
		sf::RenderWindow m_window;
 
		sf::Font m_font;
		sf::Font m_numberFont;

		// FPS COUNTER!!!!!
		sf::Text m_statistics_text;
		sf::Time m_statistics_update_time;
		std::size_t m_statistics_num_frames;


		// Specific game things
		std::vector<Ressource> pickableRessources;
		std::vector<Player> players;
		std::vector<Powerup> powerups;

		RessourceManager ressourceManager;

		int currentChief{-1};
		int currentTurn{0};

		sf::Clock turnTimer;


		// Network stuff

		Network* network;
		bool server{false};

		bool inTurn{true};

		sf::Packet currentTurnRessourcesPacket;



};

#endif // HEADER_GAME