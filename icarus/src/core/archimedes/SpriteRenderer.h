#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>

#include "Actor.h"

// SpriteRenderer.h
//
// Component that when attached to an Actor can draw an image to the screen.
namespace Archimedes
{
	class SpriteRenderer : public Actor
	{
	public:

		SpriteRenderer(const std::string& texturePath) : Actor("SpriteRenderer"), sprite(texture)
		{
			if (!texture.loadFromFile(texturePath))
			{
				//TODO error
			}
			sprite.setTexture(texture);
		}

		void Initialize() override
		{
			auto parentActor = GetParent();
			if (parentActor)
			{
				transform = parentActor->transform;
			}
		}

		void Update(float deltaTime) override
		{
			auto parentActor = GetParent();
			if (parentActor)
			{
				transform = parentActor->transform;
				transform.Apply(sprite);
			}
		}
	protected:
		sf::Texture texture;
		sf::Sprite sprite;
	};
}