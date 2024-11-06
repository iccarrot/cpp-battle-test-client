#pragma once

namespace sw::simulation
{
	class NonCopyable
	{
	public:
		constexpr NonCopyable() = default;
		~NonCopyable() = default;

		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;
	};
}
