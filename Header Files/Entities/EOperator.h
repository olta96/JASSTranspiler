#pragma once
#include "Entity.h"
#include "AccessModifiable.h"
#include "StaticModifiable.h"
#include "Returner.h"
#include "CarriesBody.h"

namespace Entities
{
	class EOperator : public Entity, public AccessModifiable, public StaticModifiable, public Returner, public CarriesBody
	{
	public:
		EOperator(const std::string& name, const EType& returnType, const Tokenizer::Tokens::const_iterator& bodyBegin, const Tokenizer::Tokens::const_iterator& bodyEnd);

	};
}
