#pragma once

#include <SFML/Graphics.hpp>

#include "Engine/GameObject.h"
#include "Cake.h"
#include <Bonus.h>

class Player : public gloutrobate::GameObject {
private:
	sf::Vector2f _initPos;

	sf::Keyboard::Key _upKey{ sf::Keyboard::Unknown };
	sf::Keyboard::Key _downKey{ sf::Keyboard::Unknown };
	sf::Keyboard::Key _leftKey{ sf::Keyboard::Unknown };
	sf::Keyboard::Key _rightKey{ sf::Keyboard::Unknown };

	bool _canJump{ true };

	uint8 _score{ 0 };
	float maxSpeed = 6;
	float maxJump = 11;

public:
	Player(sf::Vector2f pos, sf::Vector2f size, sf::Texture const& text) : GameObject(pos, size, text), _initPos{ pos } {};

	void setKeys(sf::Keyboard::Key upKey, sf::Keyboard::Key leftKey, sf::Keyboard::Key downKey, sf::Keyboard::Key rightKey);

	void resetJump(bool jump = true) { _canJump = jump; }

	void start() override;
	void update() override;

	void applyBonus(Bonus::BonusType bonus);

	void onCollisionEnter(GameObject* other, b2Contact* contact) override;
	void onCollisionExit(GameObject* other, b2Contact* contact) override;

	virtual void onKeyPressed(sf::Event e);

	void incrScore() { _score++; };
	uint8 getScore() const { return _score; };
};
