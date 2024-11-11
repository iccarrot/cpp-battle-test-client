#pragma once

#include "Simulation/Config.hpp"
#include "Simulation/Services/Service.hpp"
#include "Simulation/Services/WorldService/World.hpp"

#include <filesystem>
#include <unordered_set>

namespace sw::simulation
{
	class WorldService final : public Service<WorldService>
	{
	public:
		using WorldPtr = std::unique_ptr<World>;
		using WorldPtrs = std::vector<WorldPtr>;
		using WorldID = uint8_t;
		using LoadingWorlds = std::unordered_set<std::filesystem::path>;

	public:
		void loadWorld(const std::filesystem::path& path);

	private:
		void update(const Turn turn) override;

		LoadingWorlds	m_loadingWorlds;
		WorldPtrs		m_worlds;
	};
}