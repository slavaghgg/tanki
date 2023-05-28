#pragma once 
#include <SFML/Graphics.hpp> 
#include "settings.h" 
#include "gameObj.h" 
class Let : public gameObj {
public:
	Let(sf::Vector2f pos) {
		texture.loadFromFile(LET_FILE_NAME);
		sprite.setTexture(texture);
		sprite.setPosition(pos);
	}
	void update() {}
	void setRandomPosition() {
		float x = rand() % 301 - 300.f;
		int choice = rand() % 10000;
		if (choice < 5000) x += 1500.f;
		float y = rand() % 301 - 300.f;
		choice = rand() % 10000;
		if (choice < 5000) y += 1200.f;
		sprite.setPosition(x, y);
		float speedx = rand() % 9 - 4.f;
		float speedy = rand() % 9 - 4.f;
	}

	void draw(sf::RenderWindow& window) { window.draw(sprite); }
};