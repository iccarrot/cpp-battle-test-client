#include <IO/Events/MapCreated.hpp>
#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/System/EventLog.hpp>
#include <Simulation/Simulation.hpp>
#include <iostream>

int main(int argc, char** argv)
{
	using namespace sw;
	using namespace sw::simulation;

	if (argc != 2)
	{
		throw std::runtime_error("Error: No file specified in command line argument");
	}

	Simulation::Cfg cfg;
	cfg.m_simulationPath = argv[1];

	if (!cfg.m_simulationPath.has_filename() || !std::filesystem::exists(cfg.m_simulationPath))
	{
		throw std::runtime_error("Error: File not found - " + cfg.m_simulationPath.string());
	}

	Simulation simulation(std::move(cfg));
	simulation.run();

	// Code for example...

	std::cout << "\n\nEvents:\n";

	EventLog eventLog;

	eventLog.log(1, io::MapCreated{10, 10});
	eventLog.log(1, io::UnitSpawned{1, "Swordsman", 0, 0});
	eventLog.log(1, io::UnitSpawned{2, "Hunter", 9, 0});
	eventLog.log(1, io::MarchStarted{1, 0, 0, 9, 0});
	eventLog.log(1, io::MarchStarted{2, 9, 0, 0, 0});
	eventLog.log(1, io::UnitSpawned{3, "Swordsman", 0, 9});
	eventLog.log(1, io::MarchStarted{3, 0, 9, 0, 0});

	eventLog.log(2, io::UnitMoved{1, 1, 0});
	eventLog.log(2, io::UnitMoved{2, 8, 0});
	eventLog.log(2, io::UnitMoved{3, 0, 8});

	eventLog.log(3, io::UnitMoved{1, 2, 0});
	eventLog.log(3, io::UnitMoved{2, 7, 0});
	eventLog.log(3, io::UnitMoved{3, 0, 7});

	eventLog.log(4, io::UnitMoved{1, 3, 0});
	eventLog.log(4, io::UnitAttacked{2, 1, 5, 0});
	eventLog.log(4, io::UnitDied{1});
	eventLog.log(4, io::UnitMoved{3, 0, 6});

	eventLog.log(5, io::UnitMoved{2, 6, 0});
	eventLog.log(5, io::UnitMoved{3, 0, 5});

	eventLog.log(6, io::UnitMoved{2, 5, 0});
	eventLog.log(6, io::UnitMoved{3, 0, 4});

	eventLog.log(7, io::UnitAttacked{2, 3, 5, 5});
	eventLog.log(7, io::UnitMoved{3, 0, 3});

	eventLog.log(8, io::UnitAttacked{2, 3, 5, 0});
	eventLog.log(8, io::UnitDied{3});

	return 0;
}
