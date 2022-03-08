#pragma once
#include "../SourceFile.h"
#include "../FileReader/FileReader.h"

namespace SourceBuilder
{
	class Merger
	{
		const FileReader::FileReader fileReader;
		std::vector<SourceFile> sourceFiles;

	public:
		void appendSourceFile(std::string sourceFilePath);

		const std::vector<SourceFile>& getSourceFiles() const;

	};
}
