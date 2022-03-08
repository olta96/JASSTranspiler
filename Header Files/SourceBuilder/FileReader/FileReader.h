#pragma once
#include "IFileReader.h"

namespace SourceBuilder
{
	namespace FileReader
	{
		class FileReader : public IFileReader
		{
		public:
			bool readFile(const std::string& filename, std::vector<std::string>& fileLines) const;

		};
	}
}
