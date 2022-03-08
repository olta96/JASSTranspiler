#pragma once
#include "CompilerOptions.h"

namespace CompilerOptions
{
	class ICompilerOptionsInterpreter
	{
	public:
		virtual const CompilerOptions& read() = 0;

	};
}
