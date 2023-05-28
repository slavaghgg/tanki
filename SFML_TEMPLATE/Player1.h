#pragma once 
#include "settings.h" 
#include "gameObj.h" 
#include "Laser.h" 
#include <list>

class Player1 :public gameObj {
private:

	int angle;
	float speed, speedx, speedy;
	float dv = 2.f;
	float maxSpeed = 20.f;
	sf::Clock timer;
	int prevFireTime, speedBonusActivateTime;
	std::list<Laser*> lasers;
	sf::FloatRect bounds = sprite.getLocalBounds();
	int hp = 100;
	int damage = 10;
	int lives = MAX_PLAYER_LIVES;
	bool speedBonusActive = false;

public:
	Player1() : prevFireTime{ timer.getElapsedTime().asMilliseconds() } {
		texture.loadFromFile(PLAYER1_FILE_NAME);
		sprite.setTexture(texture);
		angle = 0;
		speed = 0.f;
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin(bounds.width / 2, bounds.height / 2);
		sprite.setPosition(WINDOW_WIDTH / 7, WINDOW_HEIGHT / 2);

	}
	void update() {
		speed = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			angle -= 3;
			sprite.setRotation((float)angle);
			auto bounds = sprite.getGlobalBounds();

			if (sprite.getPosition().x < 0|| sprite.getPosition().x > (WINDOW_WIDTH - bounds.width)|| sprite.getPosition().y <= 0 || sprite.getPosition().y >=
				(WINDOW_HEIGHT - bounds.height))
			{
				angle += 3;
				sprite.setRotation((float)angle);
			}
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			angle += 3;
			sprite.setRotation((float)angle);
			auto bounds = sprite.getGlobalBounds();

			if (sprite.getPosition().x < 0 || sprite.getPosition().x >(WINDOW_WIDTH - bounds.width) || sprite.getPosition().y <= 0 || sprite.getPosition().y >=
				(WINDOW_HEIGHT - bounds.height))
			{
				angle -= 3;
				sprite.setRotation((float)angle);
			}

		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			speed += dv;
			
			auto bounds = sprite.getGlobalBounds();

			if (sprite.getPosition().x < 0 || sprite.getPosition().x >(WINDOW_WIDTH - bounds.width) || sprite.getPosition().y <= 0 || sprite.getPosition().y >=
				(WINDOW_HEIGHT - bounds.height))
			{
				speed -= dv;
				
			}

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			speed -= dv;
			
			auto bounds = sprite.getGlobalBounds();

			if (sprite.getPosition().x < 0 || sprite.getPosition().x >(WINDOW_WIDTH - bounds.width) || sprite.getPosition().y <= 0 || sprite.getPosition().y >=
				(WINDOW_HEIGHT - bounds.height))
			{
				speed += dv;
				
			}
		}
		if (speed < 0) speed = 0.f;
		else if (speed > maxSpeed) speed = maxSpeed;
		speedx = speed * (float)sin(angle * PI / 180);
		speedy = -speed * (float)cos(angle * PI / 180);
		sprite.move(speedx, speedy);
		fire();
		for (auto laser : lasers) {
			laser->update();
		}
		
	}

	void fire() {
		int currTime = timer.getElapsedTime().asMilliseconds();
		if (currTime - prevFireTime > FIRE_COOLDOWN) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				auto laser = new Laser(sprite.getPosition(), angle);
				lasers.push_back(laser);
				prevFireTime = currTime;
			}
		}
	}

	void draw(sf::RenderWindow& window) {
		for (auto laser : lasers) {
			laser->draw(window);
		}
		window.draw(sprite);
	}
	int getHp() { return hp; }

	std::list<Laser*>* getLasers() { return &lasers; }
	void decreaseHp(int damage) { hp -= damage; }
	void playerAddLife() { lives++; }

	void playerMinusLife() { lives--; }
	void restoreHp() { hp = MAX_PLAYER_HP; }
	int getlives() { return lives; }
	int getDamage() { return damage; }
	void addHp(int hp);
	void addSpeed();
};

void Player1::addHp(int hp) {
	this->hp += hp;
	if (this->hp > 100) this->hp = 100;
}

void Player1::addSpeed() {
	speedBonusActive = true;
	dv *= 2;
	maxSpeed *= 2;
	speedBonusActivateTime = timer.getElapsedTime().asMilliseconds();
	if (speedBonusActivateTime >= 5000) {
		speedBonusActive = false;
	}
	if (speedBonusActive = false) {
		dv /= 2;
		maxSpeed /= 2;
	}
}