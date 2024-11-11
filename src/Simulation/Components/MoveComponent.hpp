#pragma once

#include "Simulation/Components/Component.hpp"

namespace sw::simulation
{
	struct MoveComponent final : public Component<MoveComponent>
	{
		uint32_t x = 0u;
		uint32_t y = 0u;
	};
}
