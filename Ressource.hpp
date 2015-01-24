#ifndef HEADER_RESSOURCE
#define HEADER_RESSOURCE

#include "RessourceManager.hpp"

class Ressource : public Entity {
public:
	Ressource(int x, int y, int width, int height, sf::Color color, int t) : shape(sf::Vector2f(width, height)), text(){
		shape.setFillColor(color);
		shape.setPosition(x, y);
		shape.setSize(sf::Vector2f(width, height));
		type = t;
	}

	Ressource(int x, int y, int width, int height, sf::Color color, int type, std::string t, sf::Font& f) : Ressource(x, y, width, height, color, type){
		text = sf::Text(t, f);
		text.setPosition(x, y);
		text.setCharacterSize(32);
	}

	sf::Vector2f getPosition() { return shape.getPosition(); }
	sf::Vector2f getSize() { return shape.getSize(); }

	void draw(sf::RenderTarget& target){ 
		target.draw(shape); 
		//target.draw(text);
	}

	std::string getText() {return text.getString(); }

	int getType() { 
		return type;
	}


private:
	sf::RectangleShape shape;
	sf::Text text;

	int type;

};

#endif