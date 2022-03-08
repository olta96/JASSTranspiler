#pragma once
#include "../ISettingsInterpreter.h"

namespace CompilerOptions
{
	class JSONSettingsFileInterpreter : public ISettingsInterpreter
	{
	public:
		void readSettings(CompilerOptions& compilerOptions);

	};
}
