#pragma once
#include "Entity.h"
#include "AccessModifiable.h"
#include "EVariable.h"
#include <vector>
#include "StaticModifiable.h"
#include "Returner.h"
#include "CarriesBody.h"

namespace Entities
{
	class EMethod : public Entity, public AccessModifiable, public StaticModifiable, public Returner, public CarriesBody
	{
		std::vector<EVariable> params;

	public:
		EMethod(const std::string& name, const EType& returnType, const Tokenizer::Tokens::const_iterator& bodyBegin, const Tokenizer::Tokens::const_iterator& bodyEnd);

		void emplaceParam(const EType& type, const std::string& name);

	};
}
