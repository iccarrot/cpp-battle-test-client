#include "Simulation/Systems/MoveSystem/MoveSystem.hpp"

#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/UnitMoved.hpp>

#include "Simulation/Components/MoveComponent.hpp"
#include "Simulation/Components/PositionComponent.hpp"
#include "Simulation/Services/LogService/LogService.hpp"
#include "Simulation/Services/WorldService/World.hpp"
#include "Simulation/Simulation.hpp"

#include <cstdlib>

namespace sw::simulation
{
	bool MoveSystem::update(const Turn turn, const Entity entity)
	{
		auto& entityManager = world().em();

		if (auto moveComponent = entityManager.getComponent<MoveComponent>(entity))
		{
			if (auto positionComponent = entityManager.getComponent<PositionComponent>(entity))
			{
				bool moved = false;

				if (const auto deltaX = static_cast<int64_t>(moveComponent->x) - positionComponent->x)
				{
					positionComponent->x += deltaX / std::abs(deltaX);
					moved = true;
				}

				if (const auto deltaY = static_cast<int64_t>(moveComponent->y) - positionComponent->y)
				{
					positionComponent->y += deltaY / std::abs(deltaY);
					moved = true;
				}

				if (moved)
				{
					auto& logService = simulation::instance().getService<LogService>();
					logService.log(io::UnitMoved{entity, positionComponent->x, positionComponent->y});

					if (positionComponent->x == moveComponent->x && positionComponent->y == moveComponent->y)
					{
						entityManager.removeComponent<MoveComponent>(entity);
						logService.log(io::MarchEnded{entity, positionComponent->x, positionComponent->y});
					}

					return true;
				}
			}
		}

		return false;
	}
}