#pragma once

#include <IO/System/CommandParser.hpp>

#include <filesystem>

namespace sw::simulation
{
	class World;

	class WorldParser final
	{
	public:
		explicit WorldParser(World& world);
		~WorldParser() = default;

		void parse(const std::filesystem::path& path);

	private:
		io::CommandParser	m_parser;
		World&				m_world;
	};
}