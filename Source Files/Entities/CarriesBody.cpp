#include "../../Header Files/Entities/CarriesBody.h"

namespace Entities
{
	CarriesBody::CarriesBody(const Tokenizer::Tokens::const_iterator& bodyBegin, const Tokenizer::Tokens::const_iterator& bodyEnd)
		: bodyBegin(bodyBegin), bodyEnd(bodyEnd) {}
	
	const std::string& CarriesBody::renderBody()
	{

		return rendered;
	}
}
