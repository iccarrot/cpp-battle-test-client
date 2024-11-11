#include "Simulation/Services/LogService/LogService.hpp"

namespace sw::simulation
{
	void LogService::update(const Turn turn)
	{
		m_turn = turn;
	}
}
