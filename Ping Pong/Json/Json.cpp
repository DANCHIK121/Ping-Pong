// Standart libraries
#include <string>
#include <fstream>
#include <iostream>

// Project libraries
#include <nlohmann/json.hpp>

// Project files
#include "Json.h"

namespace JsonLogic
{
	Json::Json()
	{
		Json::jsonObject = new nlohmann::json();
		Json::settingsFilePath = "\\Json\\Settings.json";
	}

	nlohmann::json Json::ReadFromFile()
	{
		std::ifstream readFromFileObject(Json::GetDirectory() + Json::settingsFilePath);

		nlohmann::json dataFromFile = nlohmann::json::parse(readFromFileObject);

		readFromFileObject.close();

		return dataFromFile;
	}

	void Json::WriteToFromFile(nlohmann::json jsonData)
	{
		// Open write stream
		std::ofstream writeToFile(Json::GetDirectory() + Json::settingsFilePath);

		if (writeToFile.is_open())
		{
			// Write to file
			writeToFile << jsonData;
		}

		writeToFile.close();
	}

	std::string Json::GetDirectory()
	{
		std::string str;

		// Deprecated
		/*TCHAR buffer[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, buffer, MAX_PATH);
		std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		str = converter.to_bytes(std::wstring(buffer).substr(0, pos));*/

		// Actual
		std::filesystem::path currentPath = std::filesystem::current_path();
		str = currentPath.string();

		return str;
	}
}