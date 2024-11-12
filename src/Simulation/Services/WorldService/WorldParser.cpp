#include "Simulation/Services/WorldService/WorldParser.hpp"

#include <IO/Events/MapCreated.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>

#include "Simulation/Components/HealthComponent.hpp"
#include "Simulation/Components/MeleeAttackComponent.hpp"
#include "Simulation/Components/MoveComponent.hpp"
#include "Simulation/Components/PositionComponent.hpp"
#include "Simulation/Components/RangeAttackComponent.hpp"
#include "Simulation/Services/LogService/LogService.hpp"
#include "Simulation/Services/WorldService/World.hpp"
#include "Simulation/Simulation.hpp"

#include <fstream>

namespace sw::simulation
{
	WorldParser::WorldParser(World& world)
		: m_world{ world }
	{
		auto& logService = simulation::instance().getService<LogService>();

		//-- TODO: switch from direct instantiation to commands query
		m_parser.add<io::CreateMap>([this, &logService](auto command)
				{
					m_world.setWidth(command.width);
					m_world.setHeight(command.height);

					logService.log(io::MapCreated{command.width, command.height});
				})
			.add<io::SpawnSwordsman>([this, &logService](auto command)
				{
					auto& entityManager = m_world.em();
					entityManager.createEntity(command.unitId);

					{
						auto& component = entityManager.assignComponent<PositionComponent>(command.unitId);
						component.x = command.x;
						component.y = command.y;
					}

					{
						auto& component = entityManager.assignComponent<HealthComponent>(command.unitId);
						component.hp = command.hp;
					}

					{
						auto& component = entityManager.assignComponent<MeleeAttackComponent>(command.unitId);
						component.strength = command.strength;
					}

					logService.log(
						io::UnitSpawned
						{
							command.unitId,
							"Swordsman",
							command.x,
							command.y
						});
				})
			.add<io::SpawnHunter>([this, &logService](auto command)
				{
					auto& entityManager = m_world.em();
					entityManager.createEntity(command.unitId);
					
					{
						auto& component = entityManager.assignComponent<PositionComponent>(command.unitId);
						component.x = command.x;
						component.y = command.y;
					}

					{
						auto& component = entityManager.assignComponent<HealthComponent>(command.unitId);
						component.hp = command.hp;
					}

					{
						auto& component = entityManager.assignComponent<MeleeAttackComponent>(command.unitId);
						component.strength = command.strength;
					}

					{
						auto& component = entityManager.assignComponent<RangeAttackComponent>(command.unitId);
						component.agility = command.agility;
						component.range = command.range;
					}

					logService.log(
						io::UnitSpawned
						{
							command.unitId,
							"Hunter",
							command.x,
							command.y
						});
				})
			.add<io::March>([this, &logService](auto command)
				{
					auto& entityManager = m_world.em();

					if (const auto positionComponent = entityManager.getComponent<PositionComponent>(command.unitId))
					{
						auto& moveComponent = entityManager.assignComponent<MoveComponent>(command.unitId);
						moveComponent.x = command.targetX;
						moveComponent.y = command.targetY;

						logService.log(
							io::MarchStarted
							{
								command.unitId,
								positionComponent->x,
								positionComponent->y,
								moveComponent.x,
								moveComponent.y
							});
					}
				});
	}

	void WorldParser::parse(const std::filesystem::path& path)
	{
		if (std::ifstream file{ path })
		{
			m_parser.parse(file);
		}
	}
}
