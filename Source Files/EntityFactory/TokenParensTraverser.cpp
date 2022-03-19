#include "../../Header Files/EntityFactory/TokenParensTraverser.h"
#include "../../Header Files/Tokenizer/Token.h"
#include <cassert>

namespace EntityFactory
{
	TokenParensTraverser::TokenParensTraverser(const Tokenizer::Tokens::const_iterator& tokenIt, const Tokenizer::Tokens::const_iterator& end)
		: tokenIt(tokenIt), end(end)
	{
		assert(isParamOpen());
		bracketCounter++;
	}

	bool TokenParensTraverser::operator++()
	{
		++tokenIt;
		assert(tokenIt != end);

		if (isParamOpen())
			++bracketCounter;
		else if (isParamClose())
			--bracketCounter;

		assert(bracketCounter >= 0);

		return bracketCounter == 0;
	}

	bool TokenParensTraverser::operator++(int)
	{
		bool temp = bracketCounter == 0;
		++*this;
		return temp;
	}

	Tokenizer::Tokens::const_iterator TokenParensTraverser::getTokenIt()
	{
		return tokenIt;
	}

	const Tokenizer::Tokens::const_iterator& TokenParensTraverser::cgetTokenIt() const
	{
		return tokenIt;
	}

	bool TokenParensTraverser::isParamOpen() const
	{
		using Tokenizer::TokenType;
		return tokenIt->getTokenType() == TokenType::PAREN_OPEN && tokenIt->getTokenType() != TokenType::STRING;
	}

	bool TokenParensTraverser::isParamClose() const
	{
		using Tokenizer::TokenType;
		return tokenIt->getTokenType() == TokenType::PAREN_CLOSE && tokenIt->getTokenType() != TokenType::STRING;
	}
}
