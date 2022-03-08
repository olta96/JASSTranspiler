#pragma once
#include "../ISettingsInterpreter.h"

namespace CompilerOptions
{
	class CommandLineSettingsInterpreter : public ISettingsInterpreter
	{
		const char** commandLineCompilerOptions;
		const int& commandLineCompilerOptionsCount; 

	public:
		CommandLineSettingsInterpreter(const char** commandLineCompilerOptions, const int& commandLineCompilerOptionsCount);

		void readSettings(CompilerOptions& compilerOptions);

	};
}
