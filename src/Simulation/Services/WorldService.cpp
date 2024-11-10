#include "Simulation/Services/WorldService.hpp"

#include "Simulation/Simulation.hpp"

namespace sw::simulation
{
	void WorldService::update()
	{
		simulation::instance().stop();
	}
}
