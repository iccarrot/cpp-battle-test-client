#pragma once

#include "Simulation/Config.hpp"
#include "Simulation/Components/ComponentManager.hpp"

#include <typeinfo>

namespace sw::simulation
{
	class EntityManager final : public NonCopyable
	{
		using EntityContainer				= std::list<Entity>;
		using ComponentManagerPtr			= std::unique_ptr<IComponentManager>;
		using ComponentManagerContainer		= std::unordered_map<std::size_t, ComponentManagerPtr>;

	public:
		const EntityContainer&				entities() const { return m_entities; }

		void								createEntity(const Entity entity);
		void								removeEntity(const Entity entity);

		template <typename T>
		const ComponentManager<T>*			componentManager() const;

		template <typename T>
		T&									assignComponent(const Entity entity);

		template <typename T>
		const T*							getComponent(const Entity entity) const;

		template <typename T>
		T*									getComponent(const Entity entity);

		template <typename T>
		void								removeComponent(const Entity entity);

	private:
		EntityContainer						m_entities;
		ComponentManagerContainer			m_componentManagers;
	};

	template <typename T>
	const ComponentManager<T>* EntityManager::componentManager() const
	{
		static_assert(std::is_base_of_v<IComponent, T>, "T has to be derived from Component");

		if (T::s_type == IComponent::C_INVALID_TYPE)
		{
			return nullptr;
		}

		if (const auto found = m_componentManagers.find(T::s_type); found != std::end(m_componentManagers))
		{
			return &static_cast<const ComponentManager<T>&>(*found->second);
		}

		return nullptr;
	}

	template <typename T>
	T& EntityManager::assignComponent(const Entity entity)
	{
		static_assert(std::is_base_of_v<IComponent, T>, "T has to be derived from Component");
		
		if (T::s_type == IComponent::C_INVALID_TYPE)
		{
			T::s_type = typeid(T).hash_code();
		}

		if (auto found = m_componentManagers.find(T::s_type); found == std::end(m_componentManagers))
		{
			return static_cast<ComponentManager<T>&>(*m_componentManagers.emplace(
				T::s_type, std::make_unique<ComponentManager<T>>()).first->second).assignComponent(entity);
		}
		else
		{
			return static_cast<ComponentManager<T>&>(*found->second).assignComponent(entity);
		}
	}

	template <typename T>
	const T* EntityManager::getComponent(const Entity entity) const
	{
		static_assert(std::is_base_of_v<IComponent, T>, "T has to be derived from Component");

		if (T::s_type == IComponent::C_INVALID_TYPE)
		{
			return nullptr;
		}

		if (const auto found = m_componentManagers.find(T::s_type); found != std::end(m_componentManagers))
		{
			return static_cast<const ComponentManager<T>&>(*found->second).getComponent(entity);
		}
		
		return nullptr;
	}

	template <typename T>
	T* EntityManager::getComponent(const Entity entity)
	{
		static_assert(std::is_base_of_v<IComponent, T>, "T has to be derived from Component");

		if (T::s_type == IComponent::C_INVALID_TYPE)
		{
			return nullptr;
		}

		if (auto found = m_componentManagers.find(T::s_type); found != std::end(m_componentManagers))
		{
			return static_cast<ComponentManager<T>&>(*found->second).getComponent(entity);
		}
		
		return nullptr;
	}

	template <typename T>
	void EntityManager::removeComponent(const Entity entity)
	{
		static_assert(std::is_base_of_v<IComponent, T>, "T has to be derived from Component");

		if (T::s_type == IComponent::C_INVALID_TYPE)
		{
			return;
		}

		if (auto found = m_componentManagers.find(T::s_type); found != std::end(m_componentManagers))
		{
			static_cast<ComponentManager<T>&>(*found->second).removeComponent(entity);
		}
	}
}
