#include "Engine.h"

void gloutrobate::Engine::addGameObject(gloutrobate::GameObject* gameObjectPtr, bool isDynamic) {
	_gameObjects.push_back(gameObjectPtr);
	if (isDynamic) {
		_physicEngine.createDynamicBody(gameObjectPtr, 1.0f);
	}
	else {
		_physicEngine.createStaticBody(gameObjectPtr);
	}
}

void gloutrobate::Engine::drawOnFrame(sf::Drawable* drawable) {
	_graphicEngine.addDrawableForOneFrame(drawable);
}

bool gloutrobate::Engine::runFrame() {
	// 1- update whole engine (called before)

	const auto frameStart = std::chrono::steady_clock::now();

	// 2- update physics
	_physicEngine.update(_gameObjects);

	// 3- call update on all gameObjects
	std::ranges::for_each(_gameObjects.begin(), _gameObjects.end(), [](GameObject* go) { go->update(); });

	std::this_thread::sleep_until(frameStart + _millisecondsPerFrame);

	// 4- draw frame, call event handlers on all gameObjects
	return _graphicEngine.drawFrame(_gameObjects);
}
