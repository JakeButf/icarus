#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Icarus.hpp"

// Transform.h
//
// A base struct that is applied to all Actors.
// Represents their physical location in game.

namespace Archimedes
{
	struct Transform
	{
		sf::Vector2f position = { 0.0f, 0.0f };
		float rotation = 0.0f; //radians
		sf::Vector2f scale = { 1.0f, 1.0f };
		sf::Vector2f origin = { 0.0f, 0.0f };

		void Apply(sf::Sprite& sprite) const 
		{
			sprite.setPosition(position);
			sprite.setScale(scale);
			sprite.setOrigin(origin);
		}
	};
}