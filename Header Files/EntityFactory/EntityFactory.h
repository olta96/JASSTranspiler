#pragma once
#include "../Entities/EClass.h"
#include "../Tokenizer/TokenConstants.h"
#include "IEntityFactory.h"

namespace EntityFactory
{
	using namespace Entities;

	class EntityFactory : public IEntityFactory
	{
		const Tokenizer::Tokens& tokens;

		std::vector<const EType*> types;
		std::vector<std::string> renderedTemplates;

		Tokenizer::Tokens::const_iterator tokenIt;
		const Tokenizer::Tokens::const_iterator end;

		const EType voidType;
		const EType thistypeType;

	public:
		EntityFactory(const Tokenizer::Tokens& tokens);

		void buildEntities();

		const std::vector<const EType*>& getTypes() const;

	private:
		void buildClass();

		bool doesOperatorOrStatementEndAppearBeforeParenOpen(const Tokenizer::Tokens::const_iterator& classTokensEnd) const;

		bool doesKeywordPropertyAppearBeforeParenOpen(const Tokenizer::Tokens::const_iterator& classTokensEnd) const;

		bool doesKeywordOperatorAppearBeforeParenOpen(const Tokenizer::Tokens::const_iterator& classTokensEnd) const;

		void buildAttribute(EClass* const owner, const bool& isPublic);

		void buildProperty(EClass* const owner, const bool& isPublic);
		
		void buildOperator(EClass* const owner, const bool& isPublic);

		void buildMethod(EClass* const owner, const bool& isPublic);

		const EType* emplaceType(const Tokenizer::Tokens::const_iterator& toEmplace);

		const std::vector<const EType*>::const_iterator typeWithName(const std::string& name) const;

		bool isTokenItAttributeModifier() const;

	};
}
