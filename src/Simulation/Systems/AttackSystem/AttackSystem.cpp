#include "Simulation/Systems/AttackSystem/AttackSystem.hpp"

#include <IO/Events/UnitAttacked.hpp>
#include <IO/Events/UnitDied.hpp>

#include "Simulation/Components/HealthComponent.hpp"
#include "Simulation/Components/MeleeAttackComponent.hpp"
#include "Simulation/Components/PositionComponent.hpp"
#include "Simulation/Components/RangeAttackComponent.hpp"
#include "Simulation/Entity/EntityManager.hpp"
#include "Simulation/Services/LogService/LogService.hpp"
#include "Simulation/Services/WorldService/World.hpp"
#include "Simulation/Simulation.hpp"
 
namespace sw::simulation
{
namespace attack
{
	bool hasTargetToAtack(const Entity entity, EntityManager& entityManager, const bool attackIfHas)
	{
		if (auto positionComponent = entityManager.getComponent<PositionComponent>(entity))
		{
			auto& logService = simulation::instance().getService<LogService>();
			auto meleeAttackComponent = entityManager.getComponent<MeleeAttackComponent>(entity);
			auto rangeAttackComponent = entityManager.getComponent<RangeAttackComponent>(entity);

			if (!meleeAttackComponent && !rangeAttackComponent)
			{
				return false;
			}

			auto attack = [entity, &entityManager, &logService](
				const Entity target, const uint32_t power, HealthComponent* targetHealthComponent)
			{
				if (targetHealthComponent->hp <= power)
				{
					entityManager.removeEntity(target);
					logService.log(io::UnitAttacked{entity, target, power, 0u});
					logService.log(io::UnitDied{target});
				}
				else
				{
					targetHealthComponent->hp -= power;
					logService.log(io::UnitAttacked{entity, target, power, targetHealthComponent->hp});
				}
			};

			auto isInRange = [positionComponent](const int64_t targetX, const int64_t targetY, const uint8_t distance)
			{
				return std::abs(targetX - positionComponent->x) <= distance
					&& std::abs(targetY - positionComponent->y) <= distance;
			};

			std::optional<Entity> targetEntity;
			HealthComponent* targetHealth = nullptr;

			bool canAttackInRange = rangeAttackComponent;
			
			for (const auto target : entityManager.entities())
			{
				if (target == entity)
				{
					continue;
				}

				if (auto targetHealthComponent = entityManager.getComponent<HealthComponent>(target))
				{
					if (auto targetPositionComponent = entityManager.getComponent<PositionComponent>(target))
					{
						if (meleeAttackComponent && isInRange(targetPositionComponent->x, targetPositionComponent->y, 1))
						{
							if (attackIfHas)
							{
								attack(target, meleeAttackComponent->strength, targetHealthComponent);
							}

							return true;
						}

						if (rangeAttackComponent && canAttackInRange)
						{
							if (isInRange(targetPositionComponent->x, targetPositionComponent->y, 2))
							{
								canAttackInRange = false;
							}
							else if (!targetEntity && 
								isInRange(targetPositionComponent->x, targetPositionComponent->y, rangeAttackComponent->range))
							{
								targetEntity = target;
								targetHealth = targetHealthComponent;
							}
						}
					}
				}
			}

			if (targetEntity)
			{
				if (attackIfHas)
				{
					attack(*targetEntity, rangeAttackComponent->agility, targetHealth);
				}

				return true;
			}
		}

		return false;
	}
}

	bool AttackSystem::update(const Turn turn, const Entity entity)
	{
		auto& entityManager = world().em();
		return attack::hasTargetToAtack(entity, entityManager);
	}
}