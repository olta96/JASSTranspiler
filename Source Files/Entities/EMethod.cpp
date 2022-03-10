#include "../../Header Files/Entities/EMethod.h"

namespace Entities
{
	EMethod::EMethod(const std::string& name, const EType& returnType, const Tokenizer::Tokens::const_iterator& bodyBegin, const Tokenizer::Tokens::const_iterator& bodyEnd)
		: Entity(name), Returner(returnType), CarriesBody(bodyBegin, bodyEnd) {}

	void EMethod::emplaceParam(const EType& type, const std::string& name)
	{
		params.emplace_back(type, name);
	}
}
