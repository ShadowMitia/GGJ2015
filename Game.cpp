#include "Game.hpp"

Game::Game(std::string name, bool isServer)
: m_window(sf::VideoMode(1200, 800), name, sf::Style::Close)
, m_font()
, m_statistics_text()
, m_statistics_update_time()
, m_statistics_num_frames(0)
, players()
, powerups()
, ressourceManager()
, server(isServer)
{
	
	if (server){
		network = new Network(53000);
	} else {
		network = new Network(sf::IpAddress::LocalHost, 53000);
	}
	

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
		powerups.emplace_back(100 + i * 100, 100 + i * 100, PowerupShape::TRIANGLE, Effect::SPEED, sf::Color::Green);
	}
}

void Game::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	turnTimer.restart();
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

	if (server){
		// SERVER SPECIFIC EVENTS
		while (m_window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					m_window.close();
					break;

				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape){
						m_window.close();
					}
					switch (event.key.code){
						// Player 1
						case sf::Keyboard::Q:
							ressourceManager.chiefCounterPlayerRessource(0, 0);
						break;

						case sf::Keyboard::W:
							ressourceManager.chiefCounterPlayerRessource(0, 1);
						break;

						case sf::Keyboard::E:
							ressourceManager.chiefCounterPlayerRessource(0, 2);
						break;

						case sf::Keyboard::R:
							ressourceManager.chiefCounterPlayerRessource(0, 3);
						break;

						// Player 2
						case sf::Keyboard::A:
							ressourceManager.chiefCounterPlayerRessource(1, 0);
							break;

						case sf::Keyboard::S:
							ressourceManager.chiefCounterPlayerRessource(1, 1);
							break;

						case sf::Keyboard::D:
							ressourceManager.chiefCounterPlayerRessource(1, 2);
							break;

						case sf::Keyboard::F:
							ressourceManager.chiefCounterPlayerRessource(1, 3);
							break;

						// Player 3
						case sf::Keyboard::Y:
							ressourceManager.chiefCounterPlayerRessource(2, 0);
						break;

						case sf::Keyboard::X:
							ressourceManager.chiefCounterPlayerRessource(2, 1);
						break;

						case sf::Keyboard::C:
							ressourceManager.chiefCounterPlayerRessource(2, 2);
						break;

						case sf::Keyboard::V:
							ressourceManager.chiefCounterPlayerRessource(2, 3);
						break;

						default:
							break;
					}
					break;

				default:
					break;
			}

		// END SERVER SPECIFIC EVENTS
		}
	} else {
		// CLIENT SPECIFIC EVENTS

		while (m_window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					m_window.close();
					break;

				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape){
						m_window.close();
					}
					break;

				default:
					break;
			}
		}

		for (Player& p : players){
			if ( p.getNumber() == currentChief){
				break;
			}
			p.handleInputs();
		}

		// END CLIENT SPECIFIC EVENTS
	}
}

void Game::update(sf::Time elapsedTime) {
	if (server){
		// SERVER UPDATE
		
		ressourceManager.printDebug();
		
		// END SERVER UPDATE

	} else {
		// CLIENT UPDATE
		
		if (inTurn){
			for (Player& p : players){
				if ( p.getNumber() == currentChief){
					break;
				}
				p.update(elapsedTime);	
			}

			for (Player& p : players){
				if ( p.getNumber() == currentChief){
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
						} else if (pu.getEffect() == Effect::SLOW_DOWN){
							for (Player& player : players){
								if (player.getNumber() != p.getNumber()){
									player.applySlowDownEffect();
								}
							}
							pu.destroy();
						}
					}
				}

				if (turnTimer.getElapsedTime() > sf::seconds(30)){
					inTurn = false;
					for (int i = 0; i < ressourceManager.getCurrentTurnRessources().size(); i++){
						for (int j = 0; j < ressourceManager.getCurrentTurnRessources()[i].size(); i++){
							currentTurnRessourcesPacket << ressourceManager.getCurrentTurnRessources()[i][j];
						}
					}
					network->send(currentTurnRessourcesPacket);
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
		    

		    // END CLIENT UPDATE
		}
	}
}

void Game::render() {
	if (server){
		// SERVER RENDERING
		m_window.clear();
		sf::Text serverText("Server", m_font, 200);
		serverText.setPosition(200, 200);
		m_window.draw(serverText);
		m_window.display();
		
		// END SERVER RENDERING
	} else {
		// CLIENT RENDERING
		m_window.clear();
		if (inTurn){

			//ressourceManager.printDebug();
			for (Ressource& e : pickableRessources) { e.draw(m_window); }
			for (Powerup& pu : powerups) { pu.draw(m_window); }
			for (Player& p : players) {
				if ( p.getNumber() == currentChief){
					break;
				}
				p.draw(m_window); 
			}
		} else {
			Stats::drawCurrentTurnRessources(m_window, ressourceManager, currentChief);
			Stats::drawCurrentTurnValuesRessources(m_window, ressourceManager, currentChief, currentTurn);
		}


		//m_window.draw(m_statistics_text);
		
		m_window.display();
		// END CLIENT RENDERING
	}

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
