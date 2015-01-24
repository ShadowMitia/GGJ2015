#include "Game.hpp"


Game::Game(std::string name)
: m_window(sf::VideoMode(800, 600), name, sf::Style::Close)
, m_font()
, m_statistics_text()
, m_statistics_update_time()
, m_statistics_num_frames(0)
, players()
, powerups()
, ressourceManager()
, currentState(State::FIRST_TURN)
{
	m_font.loadFromFile("media/Prototype.ttf");
	m_numberFont.loadFromFile("media/Prototype.ttf");
	m_statistics_text.setFont(m_font);
	m_statistics_text.setPosition(5.f, 5.f);
	m_statistics_text.setCharacterSize(18);

	// my stuff
	
	std::srand(std::time(0));

	for (int i = 0; i < 50; i++){
		pickableRessources.emplace_back(std::rand() % m_window.getSize().x, std::rand() % m_window.getSize().y, 32, 32, sf::Color::Blue, std::rand() % 4, std::to_string(i), m_font);
	}

	for (int i = 0; i < NUMBER_PLAYER; i++){
		players.emplace_back(10, 10, 32, i);
	}

	for (int i = 0; i < 5; i++) {
		powerups.emplace_back(100 + i * 100, 100 + i * 100, PowerupShape::SQUARE, Effect::SPEED, sf::Color::Green);
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
	for (Player& p : players){
		if ( !(currentState == State::FIRST_TURN) && p.getNumber() == currentChief){
			break;
		}
		p.handleInputs();
	}
}

void Game::update(sf::Time elapsedTime) {
	for (Player& p : players){
		if (! (currentState == State::FIRST_TURN) && p.getNumber() == currentChief){
			break;
		}
		p.update(elapsedTime);	
	}

	for (Player& p : players){
		if (! (currentState == State::FIRST_TURN) && p.getNumber() == currentChief){
			break;
		}
		for (auto& e : pickableRessources){
			if (Collisions::collisionPlayer(p, e)){
				ressourceManager.playerGrabRessource(p, e.getType());
				e.destroy();
			}
		}

		for(Powerup& pu : powerups){
			if (Collisions::collisionPlayer(p, pu)){
				if (pu.getEffect() == Effect::SPEED){
					p.applySpeedEffect();
					pu.destroy();
				}
			}
		}
	}

	// next bit should be refactorized

	// remove all picked up ressources
    pickableRessources.erase(std::remove_if(std::begin(pickableRessources), std::end(pickableRessources), 
    [](Entity& entity){ return entity.destroyed(); }), 
    std::end(pickableRessources));

    // remove all picked up powerups
    powerups.erase(std::remove_if(std::begin(powerups), std::end(powerups),
    	[](Powerup& pu){ return pu.destroyed(); }),
    std::end(powerups));

    // end next bit
}

void Game::render() {
	m_window.clear();
	ressourceManager.printDebug();
	for (Ressource& e : pickableRessources) { e.draw(m_window); }
	for (Powerup& pu : powerups) { pu.draw(m_window); }
	for (Player& p : players) {
		if (! (currentState == State::FIRST_TURN) && p.getNumber() == currentChief){
			break;
		} 
		p.draw(m_window); 
	}
	//m_window.draw(m_statistics_text);
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
