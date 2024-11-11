#include "Simulation/Services/ServiceManager.hpp"

namespace sw::simulation
{
	void ServiceManager::update(const Turn turn)
	{
		for (const auto& service : m_services)
		{
			service->update(turn);
		}
	}

	void ServiceManager::postUpdate(const Turn turn)
	{
		for (const auto& service : m_services)
		{
			service->postUpdate(turn);
		}
	}
}
