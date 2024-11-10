#include "Simulation/Services/ServiceManager.hpp"

namespace sw::simulation
{
	void ServiceManager::update()
	{
		for (const auto& service : m_services)
		{
			service->update();
		}
	}
}
