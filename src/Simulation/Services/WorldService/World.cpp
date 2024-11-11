#include "Simulation/Services/WorldService/World.hpp"

namespace sw::simulation
{
	void World::update(const Turn turn)
	{

	}

	void World::postUpdate(const Turn turn)
	{

	}

	void World::createEntity(const Entity entity)
	{
		m_entityManager.createEntity(entity);
	}
}
