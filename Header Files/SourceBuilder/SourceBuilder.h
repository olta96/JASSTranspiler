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
		// IntelliSense wouldn't stop complaining that the default constructor of SourceBuilder was a "deleted function" so I added empty default constructor.
		SourceBuilder();

		const std::vector<SourceFile>& getSourceFiles(const CompilerOptions::CompilerOptions& compilerOptions);

	};
}
