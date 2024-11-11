#pragma once

#include "Simulation/Components/Component.hpp"

namespace sw::simulation
{
	struct PositionComponent final : public Component<PositionComponent>
	{
		uint32_t x = 0u;
		uint32_t y = 0u;
	};
}