#include "InputContext.h"

InputContext& InputContext::GetInstance()
{
	static InputContext instance;
	return instance;
}

void InputContext::Update()
{
	UpdateKeyStates();
}

bool InputContext::IsKeyPressed(sf::Keyboard::Key key) const
{
	auto it = currentKeys.find(key);
	return it != currentKeys.end() && it->second;
}

bool InputContext::IsKeyDown(sf::Keyboard::Key key) const
{
	auto it_current = currentKeys.find(key);
	auto it_previous = previousKeys.find(key);
	return (it_current != currentKeys.end() && it_current->second) && (it_previous == previousKeys.end() || !it_previous->second);
}

bool InputContext::IsKeyUp(sf::Keyboard::Key key) const
{
	auto it_current = currentKeys.find(key);
	auto it_previous = previousKeys.find(key);
	return (it_previous != previousKeys.end() && it_previous->second) && (it_current == currentKeys.end() || !it_current->second);
}

InputContext::InputContext() {}
InputContext::~InputContext() {}

void InputContext::UpdateKeyStates()
{
	previousKeys = currentKeys;

	for (int keyInt = static_cast<int>(sf::Keyboard::Key::A);
		keyInt <= static_cast<int>(sf::Keyboard::Key::Menu);
		++keyInt) {

		sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(keyInt);
		currentKeys[key] = sf::Keyboard::isKeyPressed(key);
	}
}
