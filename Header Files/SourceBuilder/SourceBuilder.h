#pragma once
#include "ISourceBuilder.h"
#include "Locator/Locator.h"
#include "Merger/Merger.h"

namespace SourceBuilder
{
	class SourceBuilder : public ISourceBuilder
	{
		Locator locator;
		Merger merger;

	public:
		const std::vector<SourceFile>& getSourceFiles(const CompilerOptions::CompilerOptions& compilerOptions);

	};
}
