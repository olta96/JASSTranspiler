#include "../../Header Files/Entities/EOperator.h"

namespace Entities
{
	EOperator::EOperator(const std::string& name, const EType& returnType, const Tokenizer::Tokens::const_iterator& bodyBegin, const Tokenizer::Tokens::const_iterator& bodyEnd)
		: Entity(name), Returner(returnType), CarriesBody(bodyBegin, bodyEnd) {}
}
