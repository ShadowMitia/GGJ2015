#ifndef HEADER_RESSOURCE
#define HEADER_RESSOURCE

class Ressource {
public:
	Ressource(int x, int y, int width, int height, sf::Color color){
		isDestroyed = false;
		shape = sf::RectangleShape(sf::Vector2f(width, height));
		shape.setFillColor(color);
		shape.setPosition(x, y);
	}

	sf::Vector2f getPosition() { return position; }
	sf::Vector2f getSize() { return shape.getSize(); }

	void draw(sf::RenderTarget& target){ target.draw(shape); }


private:
	sf::RectangleShape shape;
	bool isDestroyed;
	sf::Vector2f position;


};

#endif