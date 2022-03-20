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

		if (tokenIt->is(PAREN_ANGLE_OPEN))
		{
			TokenParensTraverser classTokenParensTraverser(tokenIt, end);
			while (++classTokenParensTraverser)
			{
				if (!classTokenParensTraverser.cgetTokenIt()->is(SYM_COMMA))
				{
					assert(classTokenParensTraverser.cgetTokenIt()->getTokenType() == TokenType::IDENTIFIER);

					eClass->pushTemplateTypeName(classTokenParensTraverser.cgetTokenIt()->getValue().getValue());
				}
			}

			tokenIt = classTokenParensTraverser.getTokenIt();
			assert(tokenIt->is(PAREN_ANGLE_CLOSE));
			++tokenIt;
			assert(tokenIt->is(PAREN_CURLY_OPEN));
		}

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
				buildAttribute(eClass, isPublic);

			else if (doesKeywordPropertyAppearBeforeParenOpen(classTokensEnd))
				buildProperty(eClass, isPublic);

			else if (doesKeywordOperatorAppearBeforeParenOpen(classTokensEnd))
				buildOperator(eClass, isPublic);

			else
				buildMethod(eClass, isPublic);
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

	void EntityFactory::buildAttribute(EClass* const owner, const bool& isPublic)
	{
		bool isStatic = false;
		bool isConst = false;

		for (; isTokenItAttributeModifier(); ++tokenIt)
		{
			if (tokenIt->is(KW_STATIC))
				isStatic = true;
			else if (tokenIt->is(KW_CONST))
				isConst = true;
		}

		assert(tokenIt->getTokenType() == TokenType::IDENTIFIER && (tokenIt + 1)->getTokenType() == TokenType::IDENTIFIER);

		const EType* eType = emplaceType(tokenIt);
		
		++tokenIt;
		const std::string& name = tokenIt->getValue().getValue();

		EAttribute* eAttribute;

		++tokenIt;
		if (tokenIt->getTokenType() == TokenType::STATEMENT_END)
			eAttribute = owner->emplaceAttribute(*eType, name, false, tokenIt, tokenIt);
		else
		{
			assert(tokenIt->is(SS_OP_ASSIGN));
			++tokenIt;
			const Tokenizer::Tokens::const_iterator valueBegin = tokenIt;

			while (tokenIt->getTokenType() != TokenType::STATEMENT_END) ++tokenIt;
			const Tokenizer::Tokens::const_iterator valueEnd = tokenIt;

			eAttribute = owner->emplaceAttribute(*eType, name, true, valueBegin, valueEnd);
		}

		eAttribute->setPublic(isPublic);
		eAttribute->setStatic(isStatic);
		eAttribute->setConst(isConst);
	}

	void EntityFactory::buildProperty(EClass* const owner, const bool& isPublic)
	{
		while (!tokenIt->is(PAREN_CURLY_CLOSE)) ++tokenIt; // TODO
	}

	void EntityFactory::buildOperator(EClass* const owner, const bool& isPublic)
	{
		while (!tokenIt->is(PAREN_CURLY_CLOSE)) ++tokenIt; // TODO
	}

	void EntityFactory::buildMethod(EClass* const owner, const bool& isPublic)
	{
		while (!tokenIt->is(PAREN_CURLY_CLOSE)) ++tokenIt; // TODO
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
	
	bool EntityFactory::isTokenItAttributeModifier() const
	{
		return tokenIt->is(KW_STATIC) || tokenIt->is(KW_CONST);
	}
}
