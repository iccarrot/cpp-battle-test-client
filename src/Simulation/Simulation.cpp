#include "Simulation/Simulation.hpp"

#include "Simulation/Services/WorldService/WorldService.hpp"

#include <cassert>

namespace sw::simulation
{
	Simulation::InstanceHolder::InstanceHolder(Simulation& simulation)
	{
		m_instance = &simulation;
	}

	Simulation::InstanceHolder::~InstanceHolder()
	{
		m_instance = nullptr;
	}

	Simulation* Simulation::InstanceHolder::m_instance = nullptr;

	Simulation::Simulation(Cfg&& cfg)
		: m_instance{ *this }
		, m_cfg{ std::move(cfg) }
	{
		m_serviceManager.assign<WorldService>();
	}

	Simulation::~Simulation()
	{
		m_status = Status::Finalized;
	}

	void Simulation::run()
	{
		assert(m_status == Status::Initialized && "The simulation should be initialized first");
		m_serviceManager.get<WorldService>().loadWorld(m_cfg.m_simulationPath);

		Turn currentTurn = 0u;
		for (m_status = Status::Running; m_status == Status::Running;)
		{
			update(++currentTurn);
		}
	}

	void Simulation::stop()
	{
		if (m_status == Status::Running)
		{
			m_status = Status::Stopped;
		}
	}

	void Simulation::update(const Turn turn)
	{
		m_serviceManager.update(turn);
	}

	Simulation& instance()
	{
		assert(Simulation::InstanceHolder::m_instance && "Simulation hasn't ceated yet");
		return *Simulation::InstanceHolder::m_instance;
	}
}
