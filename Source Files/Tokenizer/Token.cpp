#include "../../Header Files/Tokenizer/Token.h"

namespace Tokenizer
{
	Token::Token(const Preprocessor::PreprocessedToken& value, const TokenType& tokenType) : value(value), tokenType(tokenType) {}
	
	const TokenType& Token::getTokenType() const
	{
		return tokenType;
	}
	
	const Preprocessor::PreprocessedToken& Token::getValue() const
	{
		return value;
	}

	bool Token::is(const std::string& toMatch) const
	{
		if (tokenType == TokenType::STRING || tokenType == TokenType::FOUR_CC)
			return false;

		return value.getValue() == toMatch;
	}

	bool Token::is(const char& toMatch) const
	{
		if (value.size() != 1)
			return false;

		if (tokenType == TokenType::STRING || tokenType == TokenType::FOUR_CC)
			return false;

		return value.getValue()[0] == toMatch;
	}
}
