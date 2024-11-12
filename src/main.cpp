#include <Simulation/Simulation.hpp>

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

	return 0;
}
