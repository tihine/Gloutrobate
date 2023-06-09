#pragma once

#include <string>
#include <thread>
#include <memory>
#include <functional>
#include <chrono>

#include <SFML/Graphics.hpp>

#include "Graphics.h"
#include "Physics.h"
#include "GameObject.h"

namespace gloutrobate {
	class Engine {
	private:
		Graphics _graphicEngine;
		Physics _physicEngine{};
		std::chrono::milliseconds _millisecondsPerFrame;

		std::vector<gloutrobate::GameObject*> _gameObjects;

		bool runFrame();

	public:
		Engine() = delete;
		Engine(std::string const& name, int width, int height, float pixelsPerMeter, float fps = 60) : 
			_graphicEngine{ name, width, height, static_cast<unsigned int>(fps), pixelsPerMeter }, _physicEngine{ fps }, _millisecondsPerFrame{ static_cast<int>((float)1000 / fps) } {};
		~Engine() = default;

		void addGameObject(gloutrobate::GameObject* gameObjectPtr, bool isDynamic = false);
		void drawOnFrame(sf::Drawable* drawablePtr);
		void setEventCallback(sf::Event::EventType eventType, std::function<void(sf::Event)> const& callback);

		template<typename T>
		void start(T update) {
			// 0- call start on all gameObjects
			std::ranges::for_each(_gameObjects.begin(), _gameObjects.end(), [](GameObject* go) { go->start(); });
			do {
				// 1- update whole engine
				if (!update()) break;
				// 2- update physics
				// 3- call update on all gameObjects
				// 4- draw frame, call event handlers on all gameObjects
			} while (runFrame());
		};
	};
}