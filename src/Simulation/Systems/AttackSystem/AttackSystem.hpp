#pragma once

#include "Simulation/Systems/System.hpp"

namespace sw::simulation
{
	class EntityManager;

namespace attack
{
	bool hasTargetToAtack(const Entity entity, EntityManager& entityManager, const bool attackIfHas = true);
}

	class AttackSystem final : public System<AttackSystem>
	{
	public:
		explicit AttackSystem(World& world) : System(world) {}

	private:
		bool update(const Turn turn, const Entity entity) override;
	};
}
