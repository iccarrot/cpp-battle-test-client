#pragma once

#include "Simulation/Config.hpp"

#include <limits>

namespace sw::simulation
{
	class IComponent : public NonCopyable
	{
	public:
		using Type = std::size_t;

		inline static constexpr Type C_INVALID_TYPE = std::numeric_limits<Type>::max();

	public:
		virtual ~IComponent() = default;

		virtual Type type() const { return C_INVALID_TYPE; }
	};

	template<typename T>
	class Component : public IComponent
	{
		friend class EntityManager;
		static Type s_type;

		Type type() const override { return Component::s_type; }
	};

	template <typename T>
	IComponent::Type Component<T>::s_type = IComponent::C_INVALID_TYPE;
}
