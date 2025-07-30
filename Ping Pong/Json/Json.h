#pragma once

#include <string>
#include <nlohmann/json.hpp>

namespace WorkWithJson 
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