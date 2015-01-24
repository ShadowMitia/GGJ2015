#ifndef HEADER_COLLISION
#define HEADER_COLLISION

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Ressource.hpp"
#include "Powerup.hpp"

class Collisions {
public:
	static bool collisionPlayer(Player player, Powerup pow){
		sf::FloatRect p = sf::FloatRect(player.getPosition(), player.getSize());
		return p.intersects(pow.getBounds());
	}

	template<class T>
	static bool collisionPlayer(Player player, T ressource) {
		static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity!");
		return (player.getPosition().x <= ressource.getPosition().x + ressource.getSize().x
			&& player.getPosition().x + player.getSize().x >= ressource.getPosition().x
			&& player.getPosition().y + player.getSize().y >= ressource.getPosition().y
			&& player.getPosition().y <= ressource.getPosition().y + ressource.getSize().y);
	}
};

#endif