#include "../../../Header Files/SourceBuilder/FileReader/FileReader.h"
#include <fstream>
#include "../../../Header Files/Tokenizer/TokenConstants.h"

namespace SourceBuilder
{
	namespace FileReader
	{
		bool FileReader::readFile(const std::string& filename, std::vector<std::string>& fileLines) const
		{
			using Tokenizer::TokenConstants::KW_IMPORT;

			static constexpr bool SUCCESS = true, FAILED = false;

			std::string line;
			std::fstream file(filename);

			if (file.is_open())
			{
				while (std::getline(file, line))
				{
					if (line.size() >= KW_IMPORT.size() && line.compare(0, KW_IMPORT.size(), KW_IMPORT) == 0)
						fileLines.push_back("");
					else
						fileLines.push_back(line);
				}
				file.close();
				return SUCCESS;
			}

			return FAILED;
		}
	}
}
