#pragma once
#include <string>
#include <vector>

#if _DEBUG
#include <ostream>
#endif

namespace Preprocessor
{
	class PreprocessedToken
	{
		const std::string value;
		const int line;
		const std::string& filePath;

	public:
		PreprocessedToken(const std::string& value, const int& line, const std::string& filePath);

		const std::string& getValue() const;
		const int& getLine() const;
		const std::string& getFilePath() const;

		const size_t& size() const;

#if _DEBUG
		friend std::ostream& operator<<(std::ostream& os, const PreprocessedToken& preprocessedToken);
#endif

	};

	using PreprocessedTokens = std::vector<PreprocessedToken>;
}
