#pragma once

#include "Simulation/Systems/System.hpp"

namespace sw::simulation
{
	class AtackSystem final : public System<AtackSystem>
	{
	public:
		explicit AtackSystem(World& world) : System(world) {}

	private:
		bool update(const Turn turn, const Entity entity) override;
	};
}
