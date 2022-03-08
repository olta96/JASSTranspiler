#pragma once
#include "CompilerOptions.h"

namespace CompilerOptions
{
	class ISettingsInterpreter
	{
	public:
		virtual void readSettings(CompilerOptions& compilerOptions) = 0;

	};
}
