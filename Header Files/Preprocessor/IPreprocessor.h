#pragma once
#include "PreprocessedToken.h"
#include "../SourceBuilder/SourceFile.h"

namespace Preprocessor
{
	class IPreprocessor
	{
	public:
		virtual const std::vector<PreprocessedTokens>& tokenize(const std::vector<SourceBuilder::SourceFile>& sourceFiles) = 0;
	};

}
