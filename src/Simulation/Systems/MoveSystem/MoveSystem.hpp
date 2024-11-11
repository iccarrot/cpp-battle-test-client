#pragma once

#include "Simulation/Systems/System.hpp"

namespace sw::simulation
{
	class MoveSystem final : public System<MoveSystem>
	{
	public:
		explicit MoveSystem(World& world) : System(world) {}

	private:
		bool update(const Turn turn, const Entity entity) override;
	};
}
