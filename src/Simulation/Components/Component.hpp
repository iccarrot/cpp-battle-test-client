#pragma once

#include "Simulation/Config.hpp"

#include <limits>

namespace sw::simulation
{
	class IComponent : public NonCopyable
	{
	public:
		using Type = uint8_t;

		inline static constexpr Type C_INVALID_TYPE = std::numeric_limits<Type>::max();

	public:
		virtual ~IComponent() = default;
	};

	template<typename T>
	class Component : public IComponent
	{
		friend class ServiceManager;
		static Type type;
	};

	template <typename T>
	IComponent::Type Component<T>::type = IComponent::C_INVALID_TYPE;
}
