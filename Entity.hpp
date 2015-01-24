#ifndef HEADER_ENTITY
#define HEADER_ENTITY

#include <SFML/Graphics.hpp>

class Entity {
public:
	virtual ~Entity() {};
	virtual void draw(sf::RenderTarget& target) = 0;
	virtual void update(sf::Time deltaTime) {}

	bool destroyed() { return isDestroyed; }
	void destroy() { isDestroyed = true; }

private:
	bool isDestroyed{false};

};

#endif