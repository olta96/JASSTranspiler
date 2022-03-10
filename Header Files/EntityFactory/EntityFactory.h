#pragma once
#include "../Entities/EClass.h"
#include "../Tokenizer/TokenConstants.h"

namespace EntityFactory
{
	using namespace Entities;

	class EntityFactory
	{
		const EType voidType;
		const EType thistypeType;

		std::vector<const EType*> types;
		std::vector<const std::string> renderedTemplates;

	public:
		EntityFactory();

	};
}
