#include "../../../Header Files/SourceBuilder/Locator/Locator.h"
#include <cassert>
#include <fstream>
#include "../../../Header Files/Utilities/UserOutput/UserOutput.h"
#include <deque>
#include "../../../Header Files/Tokenizer/TokenConstants.h"
#include <algorithm>

namespace SourceBuilder
{
	const std::unordered_set<std::string>& Locator::locateSourceFilePaths(const CompilerOptions::CompilerOptions& compilerOptions)
	{
		using Utilities::UserOutput;
		UserOutput& userOutput = UserOutput::getInstance();

		const std::string basePath = compilerOptions.sourceFolderPath + "/";
		sourceFilePaths.insert(basePath + compilerOptions.mainSourceFilename + "." + Globals::Constants::SOURCE_FILE_EXTENSION);
		std::deque<std::string> sourceFilePathsToSearchImportsOf { *sourceFilePaths.cbegin() };

		std::string line;
		std::string importPath;
		while (!sourceFilePathsToSearchImportsOf.empty())
		{
			const std::string& filename(sourceFilePathsToSearchImportsOf.front());
			std::fstream sourceFile(filename);

			if (sourceFile.is_open())
			{
				while (std::getline(sourceFile, line))
				{
					if (readImport(line, importPath))
					{
						if (sourceFilePaths.find(basePath + importPath) == sourceFilePaths.cend())
						{
							sourceFilePaths.insert(basePath + importPath + "." + Globals::Constants::SOURCE_FILE_EXTENSION);
							sourceFilePathsToSearchImportsOf.push_back(basePath + importPath + "." + Globals::Constants::SOURCE_FILE_EXTENSION);
						}
					}
				}
				sourceFile.close();
			}
			else
			{
				sourceFilePaths.erase(filename);
				userOutput.warn("Could not open \"" + filename + "\".");
			}

			sourceFilePathsToSearchImportsOf.pop_front();
		}

		return sourceFilePaths;
	}

	bool Locator::readImport(const std::string& line, std::string& importPath)
	{
		using Tokenizer::TokenConstants::KW_IMPORT;
		using Tokenizer::TokenConstants::SYM_STRING;

		if (line.size() < KW_IMPORT.size())
			return false;

		using Utilities::UserOutput;
		UserOutput& userOutput = UserOutput::getInstance();

		if (line.compare(0, KW_IMPORT.size(), KW_IMPORT) == 0)
		{
			if (std::count(line.cbegin(), line.cend(), SYM_STRING) == 2 && *line.crbegin() == SYM_STRING)
			{
				importPath = std::string(line.cbegin() + line.find(SYM_STRING) + 1, line.cbegin() + line.find(SYM_STRING, line.find(SYM_STRING) + 1));
				return true;
			}
			else
				userOutput.warn("Skipping malformed import: \'" + line + "\'.");
		}

		return false;
	}
}
