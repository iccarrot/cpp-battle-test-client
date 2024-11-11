#include "Simulation/Systems/SystemManager.hpp"

namespace sw::simulation
{
	void SystemManager::update(const Turn turn, const Entity entity)
	{
		for (const auto& system : m_systems)
		{
			if (system->update(turn, entity))
			{
				break;
			}
		}
	}

	void SystemManager::postUpdate(const Turn turn)
	{
		for (const auto& system : m_systems)
		{
			system->postUpdate(turn);
		}
	}
}
