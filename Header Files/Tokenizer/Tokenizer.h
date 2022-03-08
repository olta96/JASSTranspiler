#pragma once
#include "ITokenizer.h"
#include "../Preprocessor/PreprocessedToken.h"
#include "../Utilities/UserOutput/UserOutput.h"

namespace Tokenizer
{
	class Tokenizer : public ITokenizer
	{
		const std::vector<Preprocessor::PreprocessedTokens>& preprocessedTokensFiles;
		Preprocessor::PreprocessedTokens::const_iterator tokenItBegin, tokenIt, tokenItEnd;
		Tokens tokens;
		Utilities::UserOutput& userOutput = Utilities::UserOutput::getInstance();

	public:
		Tokenizer(const std::vector<Preprocessor::PreprocessedTokens>& preprocessedTokensFiles);

		const Tokens& tokenize();

	private:
		void buildToken();

		void buildTokenUsingSingleChar();

		void emplaceTokenIt(const TokenType& tokenType);

		bool isTokenItTemplateOpen() const;

		bool isTokenItTemplateClose() const;

		bool isTokenItAlNumWithLeadingAlphaOrUnderscore() const;

		bool isTokenItAlNumWithLeadingAlphaOrUnderscore(const Preprocessor::PreprocessedTokens::const_iterator& tokenIt) const;

		bool isTokenItNonKeywordAlNumWithLeadingAlphaOrUnderscore(const Preprocessor::PreprocessedTokens::const_iterator& tokenIt) const;

		bool isAlNumOrUnderscore(const char& c) const;

		bool isTokenItRealValue() const;

		void warnUnknownTokenIt() const;

	};
}
