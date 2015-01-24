#ifndef HEADER_COLLISION
#define HEADER_COLLISION

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Ressource.hpp"

class Collisions {
public:
	static bool collisionPlayerRessource(Player player, Ressource ressource) {
		return (player.getPosition().x <= ressource.getPosition().x + ressource.getSize().x
			&& player.getPosition().x + player.getSize().x >= ressource.getPosition().x
			&& player.getPosition().y + player.getSize().y >= ressource.getPosition().y
			&& player.getPosition().y <= ressource.getPosition().y + ressource.getSize().y);
	}
};

#endif