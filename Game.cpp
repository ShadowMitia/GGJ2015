#include "Game.hpp"


Game::Game(std::string name)
: m_window(sf::VideoMode(800, 600), name, sf::Style::Close)
, m_font()
, m_statistics_text()
, m_statistics_update_time()
, m_statistics_num_frames(0)
, player(m_window.getSize().x / 2, m_window.getSize().y / 2, 32 / 2)
, p(100, 100, PowerupShape::SQUARE, Effect::SPEED, sf::Color::Green)
, myStorage()
{

	m_font.loadFromFile("media/Prototype.ttf");
	m_numberFont.loadFromFile("media/Prototype.ttf");
	m_statistics_text.setFont(m_font);
	m_statistics_text.setPosition(5.f, 5.f);
	m_statistics_text.setCharacterSize(18);

	// my stuff
	
	std::srand(std::time(0));

	for (int i = 0; i < 10; i++){
		pickableRessources.emplace_back(std::rand() % m_window.getSize().x, std::rand() % m_window.getSize().y, 32, 32, sf::Color::Blue, std::to_string(i), m_font);
	}


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
	player.handleInputs();
}

void Game::update(sf::Time elapsedTime) {
	player.update(elapsedTime);

	for (auto& e : pickableRessources){
		if (Collisions::collisionPlayer(player, e)){
			//std::cout << "Collision! " << e.getText() << " X: " << e.getPosition().x << " Y: " << e.getPosition().y << std::endl; 
			e.destroy();
		}
	}

	if (Collisions::collisionPlayer(player, p)){
		if (p.getEffect() == Effect::SPEED){
			player.applySpeedEffect();
		}
	}

    pickableRessources.erase(std::remove_if(std::begin(pickableRessources), std::end(pickableRessources), 
    [](Entity& entity){ return entity.destroyed(); }), 
    std::end(pickableRessources));
}

void Game::render() {
	m_window.clear();

	for (auto e : pickableRessources) { e.draw(m_window); }
	p.draw(m_window);
	player.draw(m_window);
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
