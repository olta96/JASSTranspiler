#include "../../Header Files/CompilerOptions/CompilerOptionsInterpreter.h"
#include "../../Header Files/Utilities/UserOutput/UserOutput.h"

namespace CompilerOptions
{
	CompilerOptionsInterpreter::CompilerOptionsInterpreter(const char** commandLineCompilerOptions, const int& commandLineCompilerOptionsCount)
		: commandLineSettingsInterpreter(commandLineCompilerOptions, commandLineCompilerOptionsCount) {}

	const CompilerOptions& CompilerOptionsInterpreter::read()
	{
		using Utilities::UserOutput;
		const UserOutput& userOutput = UserOutput::getInstance();

		jsonSettingsFileInterpreter.readSettings(compilerOptions);

		commandLineSettingsInterpreter.readSettings(compilerOptions);

		userOutput.log("Compiler Options:");
		userOutput.log("\tSource Folder: \"" + compilerOptions.sourceFolderPath + "\"");
		userOutput.log("\tOut Folder: \"" + compilerOptions.outFolderPath + "\"");
		userOutput.log("\tMain Source File: \"" + compilerOptions.mainSourceFilename + "." + Globals::Constants::SOURCE_FILE_EXTENSION + "\"", "\n\n");

		return compilerOptions;
	}
}
