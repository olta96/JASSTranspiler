#pragma once
#include "ILineTokenizer.h"
#include "PreprocessedToken.h"

namespace Preprocessor
{
	class LineTokenizer : public ILineTokenizer
	{
		bool buildingString = false;
		bool buildingFourCC = false;
		PreprocessedTokens& tokensDestination;
		const int& lineCount;
		const std::string& filePath;
		const std::string::const_iterator begin, end;
		std::string::const_iterator lineIt;
		std::string currentToken;
		bool& mulitLineComment;

	public:
		LineTokenizer(const std::string& line, PreprocessedTokens& tokensDestination, const int& lineCount, const std::string& filePath, bool& mulitLineComment);

		void tokenize();

	private:
		bool handleLineIt();

		void pushLineItAsToken();

		void buildString();

		void completeStringBuilding();

		void pushAndClearCurrentToken();

		bool isLineItMultiLineCommentDeclaration() const;

		bool isLineItMultiLineCommentEnd() const;

		bool isLineItStringDeclaration() const;

		bool isLineItFourCCDeclaration() const;

		bool isLineItSpace() const;

		bool isLineItOneLineCommentDeclaration() const;

		bool isLineItAlphaOrUnderscore() const;

		bool isLineItAlNum() const;

		bool isLineItAlNumOrUnderscore() const;

		bool isLineItUnderscore() const;

		bool isLineItDecimalPoint() const;

		bool isPrevTokenDeciamlPoint() const;

		bool isCurrentTokenRealValue() const;

		bool isLineItDigitOrDecimalPoint() const;

		bool currentTokenContainsDecimalPoint() const;

		const std::string buildTokenOfCurrentSyntaxError() const;

		void throwIllegalIdentifier() const;

		void throwRealValueWithDoubleDecimalPoints() const;

		void throwIncompleteString() const;

		void throwIllegalFourCCChars(const char& illegalChar) const;

	};
}
