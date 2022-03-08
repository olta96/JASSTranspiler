#include "../../../Header Files/SourceBuilder/Merger/Merger.h"

namespace SourceBuilder
{
	void Merger::appendSourceFile(std::string sourceFilePath)
	{
		sourceFiles.push_back(SourceFile(sourceFilePath));

		fileReader.readFile(sourceFilePath, sourceFiles.back().fileLines);
	}

	const std::vector<SourceFile>& Merger::getSourceFiles() const
	{
		return sourceFiles;
	}
}
