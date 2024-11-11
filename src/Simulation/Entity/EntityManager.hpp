#pragma once

#include "Simulation/Config.hpp"
#include "Simulation/Components/ComponentManager.hpp"

#include <typeinfo>

namespace sw::simulation
{
	class EntityManager final : public NonCopyable
	{
		using EntityContainer				= std::vector<Entity>;
		using ComponentManagerPtr			= std::unique_ptr<IComponentManager>;
		using ComponentManagerContainer		= std::unordered_map<std::size_t, ComponentManagerPtr>;

	public:
		void		createEntity(const Entity entity);

		template <typename T>
		T&			assignComponent(const Entity entity);

		template <typename T>
		const T*	getComponent(const Entity entity) const;

		template <typename T>
		T*			getComponent(const Entity entity);

	private:
		EntityContainer				m_entities;
		ComponentManagerContainer	m_componentManagers;
	};

	template <typename T>
	T& EntityManager::assignComponent(const Entity entity)
	{
		static_assert(std::is_base_of_v<IComponent, T>, "T has to be derived from IComponent");
		
		const auto hash = typeid(T).hash_code();

		if (auto found = m_componentManagers.find(hash); found == std::end(m_componentManagers))
		{
			return static_cast<ComponentManager<T>&>(*m_componentManagers.try_emplace(
				hash, std::make_unique<ComponentManager<T>>()).first->second).assignComponent(entity);
		}
		else
		{
			return static_cast<ComponentManager<T>&>(*found->second).assignComponent(entity);
		}
	}

	template <typename T>
	const T* EntityManager::getComponent(const Entity entity) const
	{
		static_assert(std::is_base_of_v<IComponent, T>, "T has to be derived from IComponent");

		if (const auto found = m_componentManagers.find(typeid(T).hash_code()); found != std::end(m_componentManagers))
		{
			return static_cast<const ComponentManager<T>&>(*found->second).getComponent(entity);
		}
		
		return nullptr;
	}

	template <typename T>
	T* EntityManager::getComponent(const Entity entity)
	{
		static_assert(std::is_base_of_v<IComponent, T>, "T has to be derived from IComponent");

		if (auto found = m_componentManagers.find(typeid(T).hash_code()); found != std::end(m_componentManagers))
		{
			return static_cast<ComponentManager<T>&>(*found->second).getComponent(entity);
		}
		
		return nullptr;
	}
}
