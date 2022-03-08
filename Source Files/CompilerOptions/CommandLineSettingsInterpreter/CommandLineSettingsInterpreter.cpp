#include "../../../Header Files/CompilerOptions/CommandLineSettingsInterpreter/CommandLineSettingsInterpreter.h"
#include "../../../Header Files/Utilities/UserOutput/UserOutput.h"

namespace CompilerOptions
{
	CommandLineSettingsInterpreter::CommandLineSettingsInterpreter(const char** commandLineCompilerOptions, const int& commandLineCompilerOptionsCount)
		: commandLineCompilerOptions(commandLineCompilerOptions), commandLineCompilerOptionsCount(commandLineCompilerOptionsCount) {}
	
	void CommandLineSettingsInterpreter::readSettings(CompilerOptions& compilerOptions)
	{
		using namespace Globals::Constants;

		Utilities::UserOutput& userOutput = Utilities::UserOutput::getInstance();

		if (commandLineCompilerOptionsCount < 2)
			return;

		if (commandLineCompilerOptionsCount % 2 == 0)
		{
			userOutput.warn("Ignoring command line compiler options. Command line compiler options are malformed. Each option needs a value.");
			return;
		}

		for (const char** cmdLineArgPtr = commandLineCompilerOptions + 1; cmdLineArgPtr != commandLineCompilerOptions + commandLineCompilerOptionsCount; cmdLineArgPtr += 2)
		{
			if (strcmp(*cmdLineArgPtr, COMPILER_OPTION_NAME_SOURCE_FOLDER_PATH) == 0)
				compilerOptions.sourceFolderPath = *(cmdLineArgPtr + 1);
			else if (strcmp(*cmdLineArgPtr, COMPILER_OPTION_NAME_OUT_FOLDER_PATH) == 0)
				compilerOptions.outFolderPath = *(cmdLineArgPtr + 1);
			else if (strcmp(*cmdLineArgPtr, COMPILER_OPTION_NAME_MAIN_SOURCE_FILENAME) == 0)
				compilerOptions.mainSourceFilename = *(cmdLineArgPtr + 1);
			else
			{
				userOutput.warn("Unknown compiler option \"" + std::string(*cmdLineArgPtr) + "\". Skipping remaining command line compiler options.");
				return;
			}
		}
	}
}
