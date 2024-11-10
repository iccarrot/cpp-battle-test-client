#pragma once

#include "Simulation/Config.hpp"
#include "Simulation/Services/Service.hpp"

#include <cassert>
#include <memory>
#include <vector>

namespace sw::simulation
{
	class ServiceManager final : public NonCopyable
	{
	public:
		using ServicePtr = std::unique_ptr<sw::simulation::IService>;
		using ServiceContainer = std::vector<ServicePtr>;

	public:
		template <typename T>
		void		assign();

		template <typename T>
		const T&	get() const;

		template <typename T>
		T&			get();

		void		update();

	private:
		ServiceContainer m_services;
	};

	template <typename T>
	void ServiceManager::assign()
	{
		static_assert(std::is_base_of_v<IService, T>, "T has to be derived from IService");

		if (T::type == IService::C_INVALID_TYPE)
		{
			m_services.emplace_back(std::make_unique<T>());
			T::type = m_services.size() - 1;
		}
		else
		{
			assert(!"Service already assign");
		}
	}

	template <typename T>
	const T& ServiceManager::get() const
	{
		static_assert(std::is_base_of_v<IService, T>, "T has to be derived from IService");
		assert(T::type != IService::C_INVALID_TYPE && "Service has to be assign first");

		return *m_services[T::Type];
	}

	template <typename T>
	T& ServiceManager::get()
	{
		static_assert(std::is_base_of_v<IService, T>, "T has to be derived from IService");
		assert(T::type != IService::C_INVALID_TYPE && "Service has to be assign first");

		return *m_services[T::Type];
	}
}
