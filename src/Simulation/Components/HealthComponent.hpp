#pragma once

#include "Simulation/Components/Component.hpp"

namespace sw::simulation
{
	struct HealthComponent final : public Component<HealthComponent>
	{
		uint32_t hp = 0u;
	};
}
