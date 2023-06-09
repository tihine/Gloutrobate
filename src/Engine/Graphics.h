#pragma once

#include <string>
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>

#include "GameObject.h"

namespace gloutobate {
	class Graphics {
	private:
		sf::RenderWindow renderWindow;

		std::vector<gloutobate::GameObject*> gameObjects{};
		std::vector<sf::Drawable*> drawables{};

		Graphics();

	public:
		Graphics(int width, int height, std::string const& name) : renderWindow{ sf::VideoMode(width, height), name } {}
		~Graphics() = default;

		bool drawFrame(std::function<void(sf::Event)> const&);

		void addGameObject(gloutobate::GameObject*);

		// Should be called before drawFrame, only for texts or other custom drawables
		void addDrawableForOneFrame(sf::Drawable*);
	};
}