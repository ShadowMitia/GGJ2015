#include "Game.hpp"


Game::Game(std::string name)
: m_window(sf::VideoMode(640, 480), name, sf::Style::Close)
, m_font()
, m_statistics_text()
, m_statistics_update_time()
, m_statistics_num_frames(0)

{

	m_font.loadFromFile("media/Prototype.ttf");
	m_numberFont.loadFromFile("media/Prototype.ttf");
	m_statistics_text.setFont(m_font);
	m_statistics_text.setPosition(5.f, 5.f);
	m_statistics_text.setCharacterSize(18);


	// network stuff
	
	if (socket.bind(5400) != sf::Socket::Done){
		std::cerr << "We have a socket error" << std::endl;
	}

	packet << "Hello, World!";
	socket.send(packet, "localhost", 54001);
}

void Game::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (m_window.isOpen()) {
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TIME_PER_FRAME) {
			timeSinceLastUpdate -= TIME_PER_FRAME;

			processEvents();
			update(TIME_PER_FRAME);
		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				m_window.close();
				break;

			default:
				break;
		}
	}
}

void Game::update(sf::Time elapsedTime) {

}

void Game::render() {
	m_window.clear();

	m_window.draw(m_statistics_text);
	m_window.display();
}

void Game::updateStatistics(sf::Time elapsedTime) {
	std::stringstream ss;

	m_statistics_update_time += elapsedTime;
	m_statistics_num_frames += 1;

	if (m_statistics_update_time >= sf::seconds(1.0f)) {
		ss << "Frames / Second = " << m_statistics_num_frames << std::endl;
		//ss << "Time / Update = " << m_statistics_update_time.asMicroseconds() / m_statistics_num_frames << " us" << std::endl;
		m_statistics_text.setString(ss.str());
							 
		m_statistics_update_time -= sf::seconds(1.0f);
		m_statistics_num_frames = 0;
	}
}
