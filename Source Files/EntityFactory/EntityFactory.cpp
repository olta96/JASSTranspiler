#include "../../Header Files/EntityFactory/EntityFactory.h"
#include "../../Header Files/Tokenizer/TokenType.h"
#include "../../Header Files/EntityFactory/TokenParensTraverser.h"
#include <cassert>


namespace EntityFactory
{
	using namespace Tokenizer::TokenConstants;
	using Tokenizer::TokenType;

	EntityFactory::EntityFactory(const Tokenizer::Tokens& tokens)
		:
			tokens(tokens),
			end(tokens.cend()),
			voidType(LIT_T_VOID),
			thistypeType(LIT_T_THISTYPE)
	{
		types.push_back(&voidType);
		types.push_back(&thistypeType);
	}

	void EntityFactory::buildEntities()
	{
		tokenIt = tokens.cbegin();

		for (; tokenIt != end;)
		{
			if (tokenIt->is(KW_CLASS))
				buildClass();
		}
	}

	void EntityFactory::buildClass()
	{
		++tokenIt;
		assert(tokenIt->getTokenType() == TokenType::IDENTIFIER);
		const std::string& className = tokenIt->getValue().getValue();

		++tokenIt;
		assert(tokenIt->is(PAREN_BRACKET_OPEN) && tokenIt->getTokenType() != TokenType::STRING);

		TokenParensTraverser classTokenParensTraverser(tokenIt, end);

		while (++classTokenParensTraverser);

		++tokenIt; // begin, after '{'
		const Tokenizer::Tokens::const_iterator& classTokensEnd = classTokenParensTraverser.cgetTokenIt(); // end, at '}'


	}
}
