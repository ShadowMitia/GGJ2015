#ifndef HEADER_PLAYER
#define HEADER_PLAYER

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Entity.hpp"

class Player : public Entity {
	public:
		constexpr static float speed = 10;
		constexpr static float deadZoneRadius = 50;


		Player(float x, float y, float radius, int playerNumber) : shape(radius) {
			shape.setPosition(x, y);
			velocity.x = speed;
			velocity.y = speed;
			number = playerNumber;
			std::cout << playerNumber << number;
			playerName.setString(std::to_string(number));
		}

		void update(sf::Time deltaTime) {
			if (( std::abs(speedAxis.x) > deadZoneRadius || std::abs(speedAxis.y) > deadZoneRadius) && isMoving) {
				shape.move(velocity.y * speedAxis.x * deltaTime.asSeconds(), velocity.y * speedAxis.y * deltaTime.asSeconds());
			}

			if (timerActive){
				if ( std::abs(timerStart.asSeconds() - effectTimer.getElapsedTime().asSeconds()) > effectTimeLength.asSeconds()){
					timerActive = false;
					velocity.x = speed;
					velocity.y = speed;
				}
			}
		}

		void draw(sf::RenderTarget& target){
			target.draw(shape);
		}

		sf::Vector2f getPosition() { return shape.getPosition(); }
		sf::Vector2f getSize() { return sf::Vector2f(shape.getRadius() * 2, shape.getRadius() * 2); }

		void handleInputs() {
			
			speedAxis.x = sf::Joystick::getAxisPosition(number, sf::Joystick::X);
			speedAxis.y = sf::Joystick::getAxisPosition(number, sf::Joystick::Y);

			if (sf::Joystick::isButtonPressed(number, 0) && buttonReleased){
				isMoving = true;
				buttonReleased = false;
			}

			if (!sf::Joystick::isButtonPressed(number, 0)){
				isMoving = false;
				buttonReleased = true;
			}
			
			//std::cout << "X: " << sf::Joystick::getAxisPosition(0, sf::Joystick::X) << std::endl;
			//std::cout << "Y: " << sf::Joystick::getAxisPosition(0, sf::Joystick::Y) << std::endl << std::endl;

			//std::cout << sf::Joystick::isButtonPressed(0, 2) << std::endl;
			/*
	        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left || sf::){

	        }
	        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) {

	        }
	        */
		}

		void applySpeedEffect() {
			timerStart = effectTimer.getElapsedTime();
			timerActive = true;
			velocity.x *= 2;
			velocity.y *= 2;
			effectTimeLength = sf::seconds(5);
		}

		void applySlowDownEffect() {
			timerStart = effectTimer.getElapsedTime();
			timerActive = true;
			velocity.x /= 2;
			velocity.y /= 2;
			effectTimeLength = sf::seconds(5);
		}

		int getNumber() { return number; }

	private:
		sf::CircleShape shape;
		sf::Vector2f speedAxis;
		sf::Vector2f velocity;

		sf::Clock effectTimer;
		sf::Time timerStart;
		sf::Time effectTimeLength;

		bool timerActive{false};
		bool isMoving{false};
		bool buttonReleased{true};
		int number;

		sf::Text playerName;



};

#endif // HEADER_PLAYER