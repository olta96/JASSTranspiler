#include "../../Header Files/Preprocessor/PreprocessedToken.h"

namespace Preprocessor
{
	PreprocessedToken::PreprocessedToken(const std::string& value, const int& line, const std::string& filePath) : value(value), line(line), filePath(filePath) {}

	const std::string& PreprocessedToken::getValue() const
	{
		return value;
	}

	const int& PreprocessedToken::getLine() const
	{
		return line;
	}

	const std::string& PreprocessedToken::getFilePath() const
	{
		return filePath;
	}

	const size_t& PreprocessedToken::size() const
	{
		return value.size();
	}

#if _DEBUG
	std::ostream& operator<<(std::ostream& os, const PreprocessedToken& preprocessedToken)
	{
		os << preprocessedToken.filePath << " (" << preprocessedToken.line << "): \"" << preprocessedToken.value << "\"";
		return os;
	}
#endif
}
