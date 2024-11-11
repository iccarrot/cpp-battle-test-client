#pragma once

#include "Simulation/Components/Component.hpp"

#include <memory>
#include <unordered_map>

namespace sw::simulation
{
	class IComponentManager : public NonCopyable
	{

	};

	template<typename T>
	class ComponentManager final : public IComponentManager
	{
	public:
		using ComponentPtr = std::unique_ptr<sw::simulation::IComponent>;
		using ComponentContainer = std::unordered_map<Entity, ComponentPtr>;

	public:
		T& assignComponent(const Entity entity)
		{
			if (auto found = m_components.find(entity); found == std::end(m_components))
			{
				return static_cast<T&>(*m_components.try_emplace(entity, std::make_unique<T>()).first->second);
			}
			else
			{
				return static_cast<T&>(*found->second);
			}
		}

	private:
		ComponentContainer m_components;
	};
}
