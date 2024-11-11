#include "Simulation/Systems/EndSystem/EndSystem.hpp"

#include "Simulation/Components/MoveComponent.hpp"
#include "Simulation/Services/WorldService/World.hpp"
#include "Simulation/Simulation.hpp"

namespace sw::simulation
{
	void EndSystem::postUpdate(const Turn turn)
	{
		auto& entityManager = world().em();
		auto& entities = entityManager.entities();

		if (entities.size() < 2)
		{
			simulation::instance().stop();
			return;
		}

		if (const auto componentManager = entityManager.componentManager<MoveComponent>();
			!componentManager || componentManager->empty())
		{
			simulation::instance().stop();
			return;
		}
	}
}