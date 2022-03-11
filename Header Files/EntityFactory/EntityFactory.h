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

		const EType voidType;
		const EType thistypeType;

		std::vector<const EType*> types;
		std::vector<std::string> renderedTemplates;

		Tokenizer::Tokens::const_iterator tokenIt;
		const Tokenizer::Tokens::const_iterator& end;

	public:
		EntityFactory(const Tokenizer::Tokens& tokens);

		void buildEntities();

	private:
		void buildClass();

	};
}
