#pragma once

#include "Simulation/Config.hpp"

#include <limits>

namespace sw::simulation
{
	class World;

	class ISystem : public NonCopyable
	{
	public:
		using Type = std::size_t;

		inline static constexpr Type C_INVALID_TYPE = std::numeric_limits<Type>::max();

	public:
		explicit ISystem(World& world) : m_world{ world } {}
		virtual ~ISystem() = default;

		virtual bool	update(const Turn turn, const Entity entity) { return false; }
		virtual void	postUpdate(const Turn turn) {}

		virtual Type	type() const { return C_INVALID_TYPE; }

		World&			world() { return m_world; }

	private:
		World& m_world;
	};

	template<typename T>
	class System : public ISystem
	{
		friend class SystemManager;
		static Type s_type;

	public:
		explicit System(World& world) : ISystem{ world } {}

		Type type() const override { return System::s_type; }
	};

	template <typename T>
	ISystem::Type System<T>::s_type = ISystem::C_INVALID_TYPE;
}
