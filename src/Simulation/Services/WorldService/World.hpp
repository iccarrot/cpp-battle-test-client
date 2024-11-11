#pragma once

#include "Simulation/Entity/EntityManager.hpp"

namespace sw::simulation
{
	class World final : public NonCopyable
	{
		using Width		= uint8_t;
		using Height	= uint8_t;

	public:
		void		update(const Turn turn);
		void		postUpdate(const Turn turn);

		Width		width() const { return m_width; }
		Height		height() const { return m_height; }

		void		setWidth(const Width width) { m_width = width; }
		void		setHeight(const Height height) { m_height = height; }

		void		createEntity(const Entity entity);

		template <typename T>
		T&			assignComponent(const Entity entity);

		template <typename T>
		const T*	getComponent(const Entity entity) const;

		template <typename T>
		T*			getComponent(const Entity entity);

	private:
		Width			m_width = 0u;
		Height			m_height = 0u;

		EntityManager	m_entityManager;
	};

	template <typename T>
	T& World::assignComponent(const Entity entity)
	{
		static_assert(std::is_base_of_v<IComponent, T>, "T has to be derived from IComponent");
		return m_entityManager.assignComponent<T>(entity);
	}

	template <typename T>
	const T* World::getComponent(const Entity entity) const
	{
		static_assert(std::is_base_of_v<IComponent, T>, "T has to be derived from IComponent");
		return m_entityManager.getComponent<T>(entity);
	}

	template <typename T>
	T* World::getComponent(const Entity entity)
	{
		static_assert(std::is_base_of_v<IComponent, T>, "T has to be derived from IComponent");
		return m_entityManager.getComponent<T>(entity);
	}
}