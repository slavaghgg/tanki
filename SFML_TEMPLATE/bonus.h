#pragma once
#include "gameObj.h"
#include "Player.h"
#include "Player1.h"

class Bonus : public gameObj {
public:
	enum BonusType { MEDKIT, SPEED_BOOST, MAX_BONUS_TYPE };
	Bonus(sf::Vector2f letPos, size_t bonusType);
	void update();
	void draw(sf::RenderWindow& window);
	void act(Player& player);
	void act1(Player1& player1);
	bool isToDel();
	auto getHitBox();
	void setDel();

private:
	BonusType type;
	sf::Clock timer;
	bool del = false;
};

Bonus::Bonus(sf::Vector2f letPos, size_t bonusType) {
	type = (BonusType)bonusType;
	switch (type) {
	case MEDKIT:
		texture.loadFromFile(MEDKIT_FILE_NAME);
		break;
	case SPEED_BOOST:
		texture.loadFromFile(SPEED_BOOST_FILE_NAME);
		break;
	
	}
	//texture.loadFromFile();
	sprite.setTexture(texture);
	sprite.setPosition(letPos);
	timer.restart();
}

void Bonus::update() {
	int now = timer.getElapsedTime().asMilliseconds();
	if (now > 5000) {
		del = true;
	}
}

void Bonus::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

bool Bonus::isToDel() { return del; }

auto  Bonus::getHitBox() { return sprite.getGlobalBounds(); }

void Bonus::setDel() { del = true; }

void Bonus::act(Player& player) {
	switch (type) {
	case MEDKIT:
		player.addHp(50);
		
		break;
	case SPEED_BOOST:
		player.addSpeed();
		
		break;	
	}
}
void Bonus::act1(Player1& player1) {
	switch (type) {
	case MEDKIT:
		player1.addHp(50);
		
		break;
	case SPEED_BOOST:
		player1.addSpeed();
		
		break;
	}
}