#include "../../Header Files/EntityFactory/EntityFactory.h"
#include "../../Header Files/Tokenizer/TokenType.h"
#include "../../Header Files/EntityFactory/TokenParensTraverser.h"
#include "../../Header Files/Utilities/UserOutput/UserOutput.h"
#include <cassert>
#include <algorithm>

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

		for (; tokenIt != end; ++tokenIt)
		{
			if (tokenIt->is(KW_CLASS))
				buildClass();
		}
	}

	const std::vector<const EType*>& EntityFactory::getTypes() const
	{
		return types;
	}

	void EntityFactory::buildClass()
	{
		++tokenIt;
		assert(tokenIt->getTokenType() == TokenType::IDENTIFIER);
		const std::string& className = tokenIt->getValue().getValue();

		EClass* const eClass = new EClass(className);

		++tokenIt;
		assert(tokenIt->is(PAREN_CURLY_OPEN) || tokenIt->is(PAREN_ANGLE_OPEN));

		TokenParensTraverser classTokenParensTraverser(tokenIt, end);

		while (++classTokenParensTraverser);

		++tokenIt;
		const Tokenizer::Tokens::const_iterator& classTokensEnd = classTokenParensTraverser.cgetTokenIt();

		bool isPublic = false;

		for (; tokenIt != classTokensEnd; ++tokenIt)
		{
			if ((tokenIt->is(KW_PUBLIC) || tokenIt->is(KW_PRIVATE)))
			{
				isPublic = tokenIt->is(KW_PUBLIC);

				++tokenIt;
				assert(tokenIt->getTokenType() == TokenType::ACCESS_MODIFIER_DECL_END);
			}

			else if (doesOperatorOrStatementEndAppearBeforeParenOpen(classTokensEnd))
				buildAttribute(eClass);

			else if (doesKeywordPropertyAppearBeforeParenOpen(classTokensEnd))
				buildProperty(eClass);

			else if (doesKeywordOperatorAppearBeforeParenOpen(classTokensEnd))
				buildOperator(eClass);

			else
				buildMethod(eClass);
		}

		types.emplace_back(eClass);
	}

	bool EntityFactory::doesOperatorOrStatementEndAppearBeforeParenOpen(const Tokenizer::Tokens::const_iterator& classTokensEnd) const
	{
		for (Tokenizer::Tokens::const_iterator tempTokenIt = tokenIt; tempTokenIt != classTokensEnd; ++tempTokenIt)
		{
			if (tempTokenIt->getTokenType() == TokenType::STATEMENT_END || tempTokenIt->getTokenType() == TokenType::OPERATOR)
				return true;
			else if (tempTokenIt->getTokenType() == TokenType::PAREN_OPEN)
				return false;
		}

		return false;
	}

	bool EntityFactory::doesKeywordPropertyAppearBeforeParenOpen(const Tokenizer::Tokens::const_iterator& classTokensEnd) const
	{
		for (Tokenizer::Tokens::const_iterator tempTokenIt = tokenIt; tempTokenIt != classTokensEnd; ++tempTokenIt)
		{
			if (tempTokenIt->is(KW_PROPERTY))
				return true;
			else if (tempTokenIt->getTokenType() == TokenType::PAREN_OPEN)
				return false;
		}

		return false;
	}

	bool EntityFactory::doesKeywordOperatorAppearBeforeParenOpen(const Tokenizer::Tokens::const_iterator& classTokensEnd) const
	{
		for (Tokenizer::Tokens::const_iterator tempTokenIt = tokenIt; tempTokenIt != classTokensEnd; ++tempTokenIt)
		{
			if (tempTokenIt->is(KW_OPERATOR))
				return true;
			else if (tempTokenIt->getTokenType() == TokenType::PAREN_OPEN)
				return false;
		}

		return false;
	}

	void EntityFactory::buildAttribute(EClass* const owner)
	{
		bool isStatic = false;

		if (tokenIt->is(KW_STATIC))
		{
			isStatic = true;
			++tokenIt;
		}

		assert(tokenIt->getTokenType() == TokenType::IDENTIFIER && (tokenIt + 1)->getTokenType() == TokenType::IDENTIFIER);

		const EType* eType = emplaceType(tokenIt);
		
		++tokenIt;
		const std::string& name = tokenIt->getValue().getValue();

		++tokenIt;
		if (tokenIt->getTokenType() == TokenType::STATEMENT_END)
			owner->emplaceAttribute(*eType, name, false, tokenIt, tokenIt);
		else
		{
			assert(tokenIt->is(SS_OP_ASSIGN));
			++tokenIt;
			const Tokenizer::Tokens::const_iterator valueBegin = tokenIt;

			while (tokenIt->getTokenType() != TokenType::STATEMENT_END) ++tokenIt;
			const Tokenizer::Tokens::const_iterator valueEnd = tokenIt;

			owner->emplaceAttribute(*eType, name, true, valueBegin, valueEnd);
		}
	}

	void EntityFactory::buildProperty(EClass* const owner)
	{

	}

	void EntityFactory::buildOperator(EClass* const owner)
	{

	}

	void EntityFactory::buildMethod(EClass* const owner)
	{

	}

	const EType* EntityFactory::emplaceType(const Tokenizer::Tokens::const_iterator& toEmplace)
	{
		assert(toEmplace->getTokenType() == TokenType::IDENTIFIER);

		const std::vector<const EType*>::const_iterator& eTypeIt = typeWithName(toEmplace->getValue().getValue());

		if (eTypeIt != types.cend())
			return *eTypeIt;

		types.emplace_back(new EType(toEmplace->getValue().getValue()));

		return types.back();
	}

	const std::vector<const EType*>::const_iterator EntityFactory::typeWithName(const std::string& name) const
	{
		return std::find_if(types.cbegin(), types.cend(), [&](const EType* const& eType) { return eType->getName() == name; });
	}
}
