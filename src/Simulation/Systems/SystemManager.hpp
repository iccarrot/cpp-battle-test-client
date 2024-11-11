#pragma once

#include "Simulation/Systems/System.hpp"

#include <cassert>
#include <memory>
#include <vector>

namespace sw::simulation
{
	class SystemManager final : public NonCopyable
	{
	public:
		using SystemPtr = std::unique_ptr<sw::simulation::ISystem>;
		using SystemContainer = std::vector<SystemPtr>;

	public:
		explicit SystemManager(World& world) : m_world(world) {};

		template <typename T>
		void		assign();

		template <typename T>
		const T&	get() const;

		template <typename T>
		T&			get();

		void		update(const Turn turn, const Entity entity);
		void		postUpdate(const Turn turn);

	private:
		SystemContainer	m_systems;
		World&			m_world;
	};

	template <typename T>
	void SystemManager::assign()
	{
		static_assert(std::is_base_of_v<ISystem, T>, "T has to be derived from System");

		if (T::s_type == ISystem::C_INVALID_TYPE)
		{
			T::s_type = typeid(T).hash_code();
		}

		for (const auto& system : m_systems)
		{
			if (system->type() == T::s_type)
			{
				assert(!"System already assign");
			}
		}

		m_systems.emplace_back(std::make_unique<T>(m_world));
	}

	template <typename T>
	const T& SystemManager::get() const
	{
		static_assert(std::is_base_of_v<ISystem, T>, "T has to be derived from System");
		assert(T::type != ISystem::C_INVALID_TYPE && "System has to be assign first");

		const auto found = std::find_if(std::begin(m_systems), std::end(m_systems), [](auto& system)
			{
				return system->type() == T::s_type;
			});

		assert(found != std::end(m_systems) && "System has to be assign first");

		return static_cast<const T&>(**found);
	}

	template <typename T>
	T& SystemManager::get()
	{
		static_assert(std::is_base_of_v<ISystem, T>, "T has to be derived from System");
		assert(T::s_type != ISystem::C_INVALID_TYPE && "System has to be assign first");

		auto found = std::find_if(std::begin(m_systems), std::end(m_systems), [](auto& system)
			{
				return system->type() == T::s_type;
			});

		assert(found != std::end(m_systems) && "System has to be assign first");

		return static_cast<T&>(**found);
	}
}
