#include "Simulation/Services/WorldService/WorldParser.hpp"

#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/System/PrintDebug.hpp>

#include "Simulation/Components/HealthComponent.hpp"
#include "Simulation/Components/MeleeAttackComponent.hpp"
#include "Simulation/Components/MoveComponent.hpp"
#include "Simulation/Components/PositionComponent.hpp"
#include "Simulation/Components/RangeAttackComponent.hpp"
#include "Simulation/Services/WorldService/World.hpp"

#include <fstream>

namespace sw::simulation
{
	WorldParser::WorldParser(World& world)
		: m_world{ world }
	{
		m_parser.add<io::CreateMap>([this](auto command)
				{
					m_world.setWidth(command.width);
					m_world.setHeight(command.height);

					printDebug(std::cout, command);
				})
			.add<io::SpawnSwordsman>([this](auto command)
				{
					m_world.createEntity(command.unitId);

					{
						auto& component = m_world.assignComponent<PositionComponent>(command.unitId);
						component.x = command.x;
						component.y = command.y;
					}

					{
						auto& component = m_world.assignComponent<HealthComponent>(command.unitId);
						component.hp = command.hp;
					}

					{
						auto& component = m_world.assignComponent<MeleeAttackComponent>(command.unitId);
						component.strength = command.strength;
					}

					printDebug(std::cout, command);
				})
			.add<io::SpawnHunter>([this](auto command)
				{
					m_world.createEntity(command.unitId);
					
					{
						auto& component = m_world.assignComponent<PositionComponent>(command.unitId);
						component.x = command.x;
						component.y = command.y;
					}

					{
						auto& component = m_world.assignComponent<HealthComponent>(command.unitId);
						component.hp = command.hp;
					}

					{
						auto& component = m_world.assignComponent<MeleeAttackComponent>(command.unitId);
						component.strength = command.strength;
					}

					{
						auto& component = m_world.assignComponent<RangeAttackComponent>(command.unitId);
						component.agility = command.agility;
						component.range = command.range;
					}

					printDebug(std::cout, command);
				})
			.add<io::March>([this](auto command)
				{
					auto& component = m_world.assignComponent<MoveComponent>(command.unitId);
					component.x = command.targetX;
					component.y = command.targetY;

					printDebug(std::cout, command);
				});
	}

	void WorldParser::parse(const std::filesystem::path& path)
	{
		if (std::ifstream file{ path })
		{
			std::cout << "Commands:\n";
			m_parser.parse(file);
		}
	}
}
