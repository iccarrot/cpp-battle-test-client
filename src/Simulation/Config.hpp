#pragma once

#include <cstdint>

namespace sw::simulation
{
	using Entity	= uint32_t;
	using Turn		= uint8_t;

	class NonCopyable
	{
	public:
		constexpr NonCopyable() = default;
		~NonCopyable() = default;

		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;
	};
}
