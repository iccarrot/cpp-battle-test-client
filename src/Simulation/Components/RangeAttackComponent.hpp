#pragma once

#include "Simulation/Components/Component.hpp"

namespace sw::simulation
{
	struct RangeAttackComponent final : public Component<RangeAttackComponent>
	{
		uint32_t agility = 0u;
		uint32_t range = 0u;
	};
}
