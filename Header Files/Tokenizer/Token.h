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

	};

	using Tokens = std::vector<Token>;
}
