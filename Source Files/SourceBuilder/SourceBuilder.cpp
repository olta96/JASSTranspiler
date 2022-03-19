#include "../../Header Files/SourceBuilder/SourceBuilder.h"
#include "../../Header Files/SourceBuilder/FileReader/FileReader.h"
#include "../../Header Files/Utilities/UserOutput/UserOutput.h"

namespace SourceBuilder
{
	SourceBuilder::SourceBuilder() {}

	const std::vector<SourceFile>& SourceBuilder::getSourceFiles(const CompilerOptions::CompilerOptions& compilerOptions)
	{
		using Utilities::UserOutput;
		const UserOutput& userOutput = UserOutput::getInstance();


		const std::unordered_set<std::string> sourceFilePaths = locator.locateSourceFilePaths(compilerOptions);


		userOutput.log("\nLocating imports ...\n--------------------");
		for (const std::string& sourceFilePath : sourceFilePaths)
		{
			userOutput.log("  Importing \"" + sourceFilePath + "\".");
			merger.appendSourceFile(sourceFilePath);
		}
		userOutput.log("--------------------\n\n");


		return merger.getSourceFiles();
	}
}
