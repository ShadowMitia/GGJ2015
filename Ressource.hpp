#ifndef HEADER_RESSOURCE
#define HEADER_RESSOURCE

#include <sstream>

class Ressource : public Entity {
public:
	Ressource(int x, int y, int width, int height, sf::Color color) : shape(sf::Vector2f(width, height)), text(){
		shape.setFillColor(color);
		shape.setPosition(x, y);
		shape.setSize(sf::Vector2f(width, height));
	}

	Ressource(int x, int y, int width, int height, sf::Color color, std::string t, sf::Font& f) : Ressource(x, y, width, height, color){
		text = sf::Text(t, f);
		text.setPosition(x, y);
		text.setCharacterSize(32);
	}

	sf::Vector2f getPosition() { return shape.getPosition(); }
	sf::Vector2f getSize() { return shape.getSize(); }

	void draw(sf::RenderTarget& target){ 
		target.draw(shape); 
		target.draw(text);
	}

	std::string getText() {return text.getString(); }


private:
	sf::RectangleShape shape;
	sf::Text text;

};

#endif