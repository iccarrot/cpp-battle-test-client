#pragma once

#include "Simulation/Config.hpp"

#include <filesystem>

namespace sw::simulation
{
	class Simulation final : public NonCopyable
	{
	public:
		struct InstanceHolder final
		{
			explicit InstanceHolder(Simulation& simulation);
			~InstanceHolder();

			static Simulation* m_instance;
		};

		struct Cfg final
		{
			std::filesystem::path m_simulationPath;
		};

	public:
		explicit Simulation(Cfg&& cfg);
		~Simulation() = default;

		void run();

	private:
		InstanceHolder	m_instance;
		Cfg				m_cfg;
	};

	Simulation& instance();
}
