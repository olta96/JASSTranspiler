#pragma once
#include "../CompilerOptions/CompilerOptions.h"
#include "SourceFile.h"

namespace SourceBuilder
{
	class ISourceBuilder
	{
	public:
		virtual const std::vector<SourceFile>& getSourceFiles(const CompilerOptions::CompilerOptions& compilerOptions) = 0;

	};
}
