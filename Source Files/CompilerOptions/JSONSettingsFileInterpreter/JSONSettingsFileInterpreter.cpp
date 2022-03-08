#include "../../../Header Files/CompilerOptions/JSONSettingsFileInterpreter/JSONSettingsFileInterpreter.h"
#include <fstream>
#include <iostream>
#include "../../../Header Files/json/json.hpp"
#include "../../../Header Files/Globals/Constants.h"

namespace CompilerOptions
{
	void JSONSettingsFileInterpreter::readSettings(CompilerOptions& compilerOptions)
	{
		using nlohmann::json;
		using namespace Globals::Constants;

		try
		{
			std::fstream jsonFile(JSON_SETTINGS_FILE_PATH);

			if (jsonFile.is_open())
			{
				const json settings = json::parse(jsonFile);

				if (settings.contains(COMPILER_OPTION_NAME_SOURCE_FOLDER_PATH))
					compilerOptions.sourceFolderPath = settings[COMPILER_OPTION_NAME_SOURCE_FOLDER_PATH].get<std::string>();

				if (settings.contains(COMPILER_OPTION_NAME_OUT_FOLDER_PATH))
					compilerOptions.outFolderPath = settings[COMPILER_OPTION_NAME_OUT_FOLDER_PATH].get<std::string>();
			}
			else
			{
				std::cerr << "Warning: settings.json not found!\n";
			}
		}
		catch (json::parse_error& e)
		{
			std::cerr << e.what() << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}
