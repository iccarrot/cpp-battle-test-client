#include "Simulation/Services/WorldService/World.hpp"

#include "Simulation/Simulation.hpp"

namespace sw::simulation
{
	void World::update()
	{
		simulation::instance().stop();
	}

	void World::createEntity(const Entity entity)
	{
		m_entityManager.createEntity(entity);
	}
}
