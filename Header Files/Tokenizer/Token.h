#pragma once
#include "TokenType.h"
#include "../Preprocessor/PreprocessedToken.h"

namespace Tokenizer
{
	class Token
	{
		const TokenType tokenType;
		const Preprocessor::PreprocessedToken& value;

	public:
		Token(const Preprocessor::PreprocessedToken& value, const TokenType& tokenType);

		const TokenType& getTokenType() const;
		const Preprocessor::PreprocessedToken& getValue() const;

		bool is(const std::string& toMatch) const;
		bool is(const char& toMatch) const;

	};

	using Tokens = std::vector<Token>;
}
