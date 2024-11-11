#pragma once

#include "Simulation/Config.hpp"

#include <cstdint>
#include <limits>

namespace sw::simulation
{
	class IService : public NonCopyable
	{
	public:
		using Type = uint8_t;

		inline static constexpr Type C_INVALID_TYPE = std::numeric_limits<Type>::max();

	public:
		virtual ~IService() = default;

		virtual void update(const Turn turn) {}
		virtual void postUpdate(const Turn turn) {}
	};

	template<typename T>
	class Service : public IService
	{
		friend class ServiceManager;
		static Type type;
	};

	template <typename T>
	IService::Type Service<T>::type = IService::C_INVALID_TYPE;
}
