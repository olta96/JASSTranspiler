#pragma once
#include <string>
#include <vector>

namespace SourceBuilder
{
	struct SourceFile
	{
		std::string filePath;
		std::vector<std::string> fileLines;

		SourceFile(const std::string& filePath);
	};
}
