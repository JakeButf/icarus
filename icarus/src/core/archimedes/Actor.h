#pragma once

#include <string>
#include <functional>
#include <vector>
#include <memory>
#include <algorithm>
#include <typeindex>
// Transform.h
//
// All actors have a transform component.
// This is the data that holds their transformation data within a scene.
#include "Transform.h"

#define TO_STRING( x ) #x

// CLASS_DECLARATION
//
// This macro must be included in the declaration of any subclass of Actor.
// It declares variables used in type checking.
#define CLASS_DECLARATION( classname ) \
public: \
	static const std::size_t Type; \
	virtual bool IsClassType(const std::size_t classType) const override; \

// CLASS_DEFINITION
// 
// This macro must be included in the class definition to properly initialize 
// variables used in type checking. Take special care to ensure that the 
// proper parentclass is indicated or the run-time type information will be
// incorrect. Only works on single-inheritance RTTI.
#define CLASS_DEFINITON( parentclass, childclass ) \
	const std::size_t childclass::Type = std::hash< std::string >()(TO_STRING(childclass)); \
	bool childclass : IsClassType(const std::size_t classType) const { \
		if (classType == childclass::Type) \
			return true; \
		return parentclass::IsClassType(classType); \
	} \

// Archimedes
//
// Namespace for component system
namespace Archimedes
{
	//Actor
	//
	//Base component class.
	class Actor : public std::enable_shared_from_this<Actor>
	{
	public:
		static const std::size_t Type;
		virtual bool IsClassType(const std::size_t classType) const {
			return classType == Type;
		}
	public:
		virtual ~Actor() = default;
		Actor(std::string && initialValue)
			:value(initialValue) {
			Initialize();
		}

		virtual void Initialize() = 0;
		virtual void Update(float deltaTime)
		{
			for (auto& pair : components)
			{
				pair.second->Update(deltaTime);
			}
		}
		virtual void Draw(sf::RenderWindow& window)
		{
			for (auto& pair : components)
			{
				pair.second->Draw(window);
			}
		}

		template <typename T, typename... Args>
		void AddComponent(Args&&... args)
		{
			std::unique_ptr<T> component = std::make_unique<T>(std::forward<Args>(args)...);
			component->parent = weak_from_this();
			components[typeid(T)] = std::move(component);
			component->Initialize();
		}

		template <typename T>
		T* GetComponent()
		{
			auto it = components.find(typeid(T));
			if (it != components.end())
			{
				return static_cast<T*>(it->second.get());
			}
			return nullptr;
		}

		std::shared_ptr<Actor> GetParent() const
		{
			return parent.lock();
		}

	public:
		Transform transform;
		std::string value = "Actor";
	protected:
		std::unordered_map<std::type_index, std::unique_ptr<Actor>> components;
		std::weak_ptr<Actor> parent;
	};


}