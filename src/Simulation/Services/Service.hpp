#pragma once

#include "Simulation/Config.hpp"

#include <limits>

namespace sw::simulation
{
	class IService : public NonCopyable
	{
	public:
		using Type = std::size_t;

		inline static constexpr Type C_INVALID_TYPE = std::numeric_limits<Type>::max();

	public:
		virtual ~IService() = default;

		virtual void update(const Turn turn) {}
		virtual void postUpdate(const Turn turn) {}

		virtual Type type() const { return C_INVALID_TYPE; }
	};

	template<typename T>
	class Service : public IService
	{
		friend class ServiceManager;
		static Type s_type;

		Type type() const override { return Service::s_type; }
	};

	template <typename T>
	IService::Type Service<T>::s_type = IService::C_INVALID_TYPE;
}
