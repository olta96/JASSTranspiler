#pragma once
#include "ICompilerOptionsInterpreter.h"
#include "CommandLineSettingsInterpreter/CommandLineSettingsInterpreter.h"
#include "JSONSettingsFileInterpreter/JSONSettingsFileInterpreter.h"

namespace CompilerOptions
{
	class CompilerOptionsInterpreter : public ICompilerOptionsInterpreter
	{
		CompilerOptions compilerOptions;
		CommandLineSettingsInterpreter commandLineSettingsInterpreter;
		JSONSettingsFileInterpreter jsonSettingsFileInterpreter;

	public:
		CompilerOptionsInterpreter(const char** commandLineCompilerOptions, const int& commandLineCompilerOptionsCount);

		const CompilerOptions& read();

	};
}
