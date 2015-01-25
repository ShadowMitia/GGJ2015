#ifndef HEADER_POWERUP
#define HEADER_POWERUP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "Entity.hpp"

enum class PowerupShape {SQUARE, TRIANGLE};
enum class Effect {SPEED};

class Powerup : public Entity {
public:


	Powerup(int x, int y, PowerupShape pShape, Effect effect, sf::Color color){
		text = sf::Text();
		if (pShape == PowerupShape::SQUARE){
			shape = new sf::RectangleShape(sf::Vector2f(32, 32));
		} else if (pShape == PowerupShape::TRIANGLE){
			shape = new sf::CircleShape(32, 3);
		} else {
			std::cout << "MEGA PROBLEM" << std::endl;
		}
		powerup = effect;
		shape->setFillColor(color);
		shape->setPosition(x, y);
	}

	virtual void draw(sf::RenderTarget& target){
		target.draw(*shape);
	}

	Effect getEffect() { return powerup; }

	sf::Vector2f getPosition() { return shape->getPosition(); }
	sf::FloatRect getBounds() { return shape->getGlobalBounds(); }

private:
	sf::Shape* shape;
	Effect powerup;
	sf::Text text;


};

#endif