#pragma once

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

		void		update(const Turn turn);
		void		postUpdate(const Turn turn);

	private:
		ServiceContainer m_services;
	};

	template <typename T>
	void ServiceManager::assign()
	{
		static_assert(std::is_base_of_v<IService, T>, "T has to be derived from Service");

		if (T::s_type == IService::C_INVALID_TYPE)
		{
			T::s_type = typeid(T).hash_code();
		}

		for (const auto& service : m_services)
		{
			if (service->type() == T::s_type)
			{
				assert(!"Service already assign");
			}
		}

		m_services.emplace_back(std::make_unique<T>());
	}

	template <typename T>
	const T& ServiceManager::get() const
	{
		static_assert(std::is_base_of_v<IService, T>, "T has to be derived from Service");
		assert(T::type != IService::C_INVALID_TYPE && "Service has to be assign first");

		const auto found = std::find_if(std::begin(m_services), std::end(m_services), [](auto& service)
			{
				return service->type() == T::s_type;
			});

		assert(found != std::end(m_services) && "Service has to be assign first");

		return static_cast<const T&>(**found);
	}

	template <typename T>
	T& ServiceManager::get()
	{
		static_assert(std::is_base_of_v<IService, T>, "T has to be derived from Service");
		assert(T::s_type != IService::C_INVALID_TYPE && "Service has to be assign first");

		auto found = std::find_if(std::begin(m_services), std::end(m_services), [](auto& service)
			{
				return service->type() == T::s_type;
			});

		assert(found != std::end(m_services) && "Service has to be assign first");

		return static_cast<T&>(**found);
	}
}
