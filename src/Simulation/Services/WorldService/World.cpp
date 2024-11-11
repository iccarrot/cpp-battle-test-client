#include "Simulation/Services/WorldService/World.hpp"

#include "Simulation/Systems/AtackSystem/AtackSystem.hpp"
#include "Simulation/Systems/EndSystem/EndSystem.hpp"
#include "Simulation/Systems/MoveSystem/MoveSystem.hpp"

namespace sw::simulation
{
	World::World()
		: m_systemManager(*this)
	{
		//-- the order is important
		m_systemManager.assign<AtackSystem>();
		m_systemManager.assign<MoveSystem>();
		m_systemManager.assign<EndSystem>();
	}

	void World::update(const Turn turn)
	{
		for (const auto entity : m_entityManager.entities())
		{
			m_systemManager.update(turn, entity);
		}
	}

	void World::postUpdate(const Turn turn)
	{
		m_systemManager.postUpdate(turn);
	}
}
