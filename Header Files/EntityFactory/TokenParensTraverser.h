#pragma once
#include "../Tokenizer/Token.h"

namespace EntityFactory
{
	class TokenParensTraverser
	{
		Tokenizer::Tokens::const_iterator tokenIt;
		const Tokenizer::Tokens::const_iterator& end;
		int bracketCounter = 0;

	public:
		TokenParensTraverser(const Tokenizer::Tokens::const_iterator& tokenIt, const Tokenizer::Tokens::const_iterator& end);

		bool operator++();
		bool operator++(int);

		Tokenizer::Tokens::const_iterator getTokenIt();
		const Tokenizer::Tokens::const_iterator& cgetTokenIt() const;

	private:
		bool isParamOpen() const;
		bool isParamClose() const;

	};
}
