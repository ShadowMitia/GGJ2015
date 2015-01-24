#ifndef HEADER_GAME
#define HEADER_GAME

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <sstream>
#include <iostream>

const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60.f);

class Game : private sf::NonCopyable {
	public:
		Game(std::string name);
		void run();

	private:
		void processEvents();
		void update(sf::Time elapsedTime);
		void render();

		void updateStatistics(sf::Time elapsedTime);
		

	private:

		sf::RenderWindow m_window;
 
		sf::Font m_font;
		sf::Font m_numberFont;

		sf::Text m_statistics_text;
		sf::Time m_statistics_update_time;
		std::size_t m_statistics_num_frames;


		// Network stuff
		//
		sf::UdpSocket socket;
		sf::Packet packet;

};

#endif // HEADER_GAME