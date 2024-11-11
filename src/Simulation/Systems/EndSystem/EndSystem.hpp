#pragma once

#include "Simulation/Systems/System.hpp"

namespace sw::simulation
{
	class EndSystem final : public System<EndSystem>
	{
	public:
		explicit EndSystem(World& world) : System(world) {}

	private:
		void postUpdate(const Turn turn) override;
	};
}
