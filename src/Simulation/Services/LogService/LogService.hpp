#pragma once

#include <IO/System/EventLog.hpp>

#include "Simulation/Services/Service.hpp"

namespace sw::simulation
{
	class LogService final : public Service<LogService>
	{
	public:
		template <typename T>
		void log(T&& event);

	private:
		void update(const Turn turn) override;

		EventLog	m_eventLog;
		Turn		m_turn = 0u;
	};

	template <typename T>
	void LogService::log(T&& event)
	{
		m_eventLog.log(m_turn, std::move(event));
	}
}
