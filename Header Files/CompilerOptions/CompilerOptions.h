#pragma once
#include <string>
#include "../Globals/Constants.h"

namespace CompilerOptions
{
	using namespace Globals::Constants;

	struct CompilerOptions
	{
		std::string sourceFolderPath = DEFAULT_SOURCE_FOLDER_PATH;
		std::string outFolderPath = DEFAULT_OUT_FOLDER_PATH;
		std::string mainSourceFilename = DEFAULT_MAIN_SOURCE_FILENAME;
	};
}
