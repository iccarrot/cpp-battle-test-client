#pragma once

#include "Simulation/Entity/EntityManager.hpp"
#include "Simulation/Systems/SystemManager.hpp"

namespace sw::simulation
{
	class World final : public NonCopyable
	{
		using Width		= uint8_t;
		using Height	= uint8_t;

	public:
		World();
		~World() = default;

		void			update(const Turn turn);
		void			postUpdate(const Turn turn);

		Width			width() const { return m_width; }
		Height			height() const { return m_height; }

		void			setWidth(const Width width) { m_width = width; }
		void			setHeight(const Height height) { m_height = height; }

		EntityManager&	em() { return m_entityManager; }

	private:
		Width			m_width = 0u;
		Height			m_height = 0u;

		EntityManager	m_entityManager;
		SystemManager	m_systemManager;
	};
}