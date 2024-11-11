#pragma once

#include "Simulation/Components/Component.hpp"

#include <memory>
#include <unordered_map>

namespace sw::simulation
{
	class IComponentManager : public NonCopyable
	{
	public:
		virtual ~IComponentManager() = default;

		virtual bool empty() const = 0;
	};

	template<typename T>
	class ComponentManager final : public IComponentManager
	{
	public:
		using ComponentPtr = std::unique_ptr<sw::simulation::IComponent>;
		using ComponentContainer = std::unordered_map<Entity, ComponentPtr>;

	public:
		T&			assignComponent(const Entity entity);
		const T*	getComponent(const Entity entity) const;
		T*			getComponent(const Entity entity);
		void		removeComponent(const Entity entity);
		bool		empty() const override { return m_components.empty(); }

	private:
		ComponentContainer m_components;
	};

	template <typename T>
	T& ComponentManager<T>::assignComponent(const Entity entity)
	{
		if (auto found = m_components.find(entity); found == std::end(m_components))
		{
			return static_cast<T&>(*m_components.emplace(entity, std::make_unique<T>()).first->second);
		}
		else
		{
			return static_cast<T&>(*found->second);
		}
	}

	template <typename T>
	const T* ComponentManager<T>::getComponent(const Entity entity) const
	{
		if (const auto found = m_components.find(entity); found != std::end(m_components))
		{
			return static_cast<const T*>(&*found->second);
		}

		return nullptr;
	}

	template <typename T>
	T* ComponentManager<T>::getComponent(const Entity entity)
	{
		if (auto found = m_components.find(entity); found != std::end(m_components))
		{
			return static_cast<T*>(&*found->second);
		}

		return nullptr;
	}

	template <typename T>
	void ComponentManager<T>::removeComponent(const Entity entity)
	{
		m_components.erase(entity);
	}
}
