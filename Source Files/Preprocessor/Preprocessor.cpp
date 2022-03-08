#include "../../Header Files/Preprocessor/Preprocessor.h"
#include "../../Header Files/Preprocessor/LineTokenizer.h"
#include "../../Header Files/Utilities/UserOutput/UserOutput.h"

namespace Preprocessor
{
	const std::vector<PreprocessedTokens>& Preprocessor::tokenize(const std::vector<SourceBuilder::SourceFile>& sourceFiles)
	{
		using Utilities::UserOutput;
		UserOutput& userOutput = UserOutput::getInstance();

		bool mulitLineComment;
		int lineCount;
		for (const SourceBuilder::SourceFile& sourceFile : sourceFiles)
		{
			preprocessedTokensFiles.emplace_back(PreprocessedTokens());
			mulitLineComment = false;
			lineCount = 0;
			for (const std::string& line : sourceFile.fileLines)
			{
				LineTokenizer lineTokenizer(line, preprocessedTokensFiles.back(), ++lineCount, sourceFile.filePath, mulitLineComment);
				lineTokenizer.tokenize();
			}

			if (mulitLineComment)
				userOutput.warn("In \"" + sourceFile.filePath + "\". Ending file without closing multi line comment is considered bad practice!");
		}

		return preprocessedTokensFiles;
	}
}
