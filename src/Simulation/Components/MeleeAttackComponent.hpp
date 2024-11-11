#pragma once

#include "Simulation/Components/Component.hpp"

namespace sw::simulation
{
	struct MeleeAttackComponent final : public Component<MeleeAttackComponent>
	{
		uint32_t strength = 0u;
	};
}
