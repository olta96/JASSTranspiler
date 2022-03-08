#pragma once
#include <vector>
#include <string>

namespace SourceBuilder
{
	namespace FileReader
	{
		class IFileReader
		{
		public:
			virtual bool readFile(const std::string& filename, std::vector<std::string>& fileLines) const = 0;
			
		};
	}
}
