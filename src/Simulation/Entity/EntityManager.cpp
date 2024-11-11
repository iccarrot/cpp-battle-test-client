#include "Simulation/Entity/EntityManager.hpp"

namespace sw::simulation
{
	void EntityManager::createEntity(const Entity entity)
	{
		if (auto found = std::find(std::begin(m_entities), std::end(m_entities), entity);
			found == std::end(m_entities))
		{
			m_entities.push_back(entity);
		}
	}
}