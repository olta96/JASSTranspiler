#pragma once
#include <string>

namespace Globals
{
	namespace Constants
	{
		// default compiler options
		inline constexpr const char* const DEFAULT_SOURCE_FOLDER_PATH = "src";
		inline constexpr const char* const DEFAULT_OUT_FOLDER_PATH = "out";
		inline constexpr const char* const DEFAULT_MAIN_SOURCE_FILENAME = "main";

		inline constexpr const char* const SOURCE_FILE_EXTENSION = "jpp";

		inline constexpr const char* const JSON_SETTINGS_FILE_PATH = "settings.json";

		// property names for settings.json and command line arguments
		inline constexpr const char* const COMPILER_OPTION_NAME_SOURCE_FOLDER_PATH = "sourceFolderPath";
		inline constexpr const char* const COMPILER_OPTION_NAME_OUT_FOLDER_PATH = "outFolderPath";
		inline constexpr const char* const COMPILER_OPTION_NAME_MAIN_SOURCE_FILENAME = "mainSourceFilename";

		inline constexpr size_t FOUR_CC_SIZE = 4;
	}
}
