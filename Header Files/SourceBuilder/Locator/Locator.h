#pragma once
#include <unordered_set>
#include <string>
#include "../../CompilerOptions/CompilerOptions.h"

namespace SourceBuilder
{
	class Locator
	{
		std::unordered_set<std::string> sourceFilePaths;

	public:
		const std::unordered_set<std::string>& locateSourceFilePaths(const CompilerOptions::CompilerOptions& compilerOptions);

	private:
		bool readImport(const std::string& line, std::string& importPath);
		
	};
}
