#pragma once

// Standart libraries
#include <string>

// Projects libraries
#include "../../vcpkg_installed/x64-windows/include/nlohmann/json.hpp"

namespace JsonLogic
{
	class Json 
	{
	public:
		Json();

		nlohmann::json ReadFromFile();
		void WriteToFromFile(nlohmann::json jsonData);

	private:
		std::string settingsFilePath;

		nlohmann::json* jsonObject;

		std::string GetDirectory();
	};
}