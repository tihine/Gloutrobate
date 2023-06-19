#pragma once

#include "Engine/GameObject.h"
class Cake : public gloutrobate::GameObject {
private :
	sf::Texture getCakeTexture() const;
	using GameObject::GameObject;
public:
	explicit Cake(sf::Vector2f pos) : GameObject(pos, sf::Vector2f(0.5,0.5), getCakeTexture()) {};
	
};
