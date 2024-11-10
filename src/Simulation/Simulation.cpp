#include "Simulation/Simulation.hpp"

#include "Simulation/Services/WorldService.hpp"

#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/System/CommandParser.hpp>
#include <IO/System/PrintDebug.hpp>

#include <cassert>
#include <fstream>
#include <iostream>

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
		std::ifstream file(m_cfg.m_simulationPath);
		if (!file)
		{
			throw std::runtime_error("Error: File not found - " + m_cfg.m_simulationPath.string());
		}

		assert(m_status == Status::Initialized && "The simulator should be initialized first");

		for (m_status = Status::Running; m_status == Status::Running;)
		{
			update();
		}

		std::cout << "Commands:\n";
		io::CommandParser parser;
		parser.add<io::CreateMap>([](auto command) { printDebug(std::cout, command); })
			.add<io::SpawnSwordsman>([](auto command) { printDebug(std::cout, command); })
			.add<io::SpawnHunter>([](auto command) { printDebug(std::cout, command); })
			.add<io::March>([](auto command) { printDebug(std::cout, command); });

		parser.parse(file);
	}

	void Simulation::stop()
	{
		if (m_status == Status::Running)
		{
			m_status = Status::Stopped;
		}
	}

	void Simulation::update()
	{
		m_serviceManager.update();
	}

	Simulation& instance()
	{
		assert(Simulation::InstanceHolder::m_instance && "Simulation hasn't ceated yet");
		return *Simulation::InstanceHolder::m_instance;
	}
}
