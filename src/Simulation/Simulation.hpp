#pragma once

#include "Simulation/Config.hpp"
#include "Simulation/Services/ServiceManager.hpp"

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

		enum class Status : uint8_t
		{
			Initialized = 0u,
			Stopped = Initialized,
			Running,
			Finalized
		};

	public:
		explicit Simulation(Cfg&& cfg);
		~Simulation();

		void run();
		void stop();

	private:
		void update(const Turn turn);

		InstanceHolder	m_instance;
		Cfg				m_cfg;
		ServiceManager	m_serviceManager;
		Status			m_status = Status::Initialized;
	};

	Simulation& instance();
}
