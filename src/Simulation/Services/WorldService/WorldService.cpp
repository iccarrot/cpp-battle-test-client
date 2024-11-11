#include "Simulation/Services/WorldService/WorldService.hpp"

#include "Simulation/Services/WorldService/WorldParser.hpp"
#include "Simulation/Simulation.hpp"

namespace sw::simulation
{
	void WorldService::loadWorld(const std::filesystem::path& path)
	{
		m_loadingWorlds.insert(path);
	}

	void WorldService::update(const Turn turn)
	{
		for (const auto& loadingWorld : m_loadingWorlds)
		{
			WorldParser parser{ *m_worlds.emplace_back(std::make_unique<World>()) };
			parser.parse(loadingWorld);
		}

		m_loadingWorlds.clear();
	}
}
