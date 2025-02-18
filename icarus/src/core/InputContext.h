#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>

// InputContext.h
//
// Class to provide input functions.
class InputContext
{
public:
	static InputContext& GetInstance();

	void Update();

	//Returns true when button is pressed
	bool IsKeyPressed(sf::Keyboard::Key key) const;
	bool IsKeyDown(sf::Keyboard::Key key) const;
	bool IsKeyUp(sf::Keyboard::Key key) const;
private:
	InputContext();
	~InputContext();

	std::unordered_map<sf::Keyboard::Key, bool> currentKeys;
	std::unordered_map<sf::Keyboard::Key, bool> previousKeys;

	void UpdateKeyStates();

	InputContext(const InputContext&) = delete;
	InputContext& operator=(const InputContext&) = delete;
};