#pragma once

#include "Simulation/Config.hpp"
#include "Simulation/Services/Service.hpp"

namespace sw::simulation
{
	class WorldService final : public Service<WorldService>
	{
	private:
		void update() override;
	};
}