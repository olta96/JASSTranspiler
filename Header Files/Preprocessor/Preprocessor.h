#pragma once
#include "IPreprocessor.h"

namespace Preprocessor
{
	class Preprocessor : public IPreprocessor
	{
		std::vector<PreprocessedTokens> preprocessedTokensFiles;

	public:
		const std::vector<PreprocessedTokens>& tokenize(const std::vector<SourceBuilder::SourceFile>& sourceFiles);

	};
}
