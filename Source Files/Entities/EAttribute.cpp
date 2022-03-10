#include "../../Header Files/Entities/EAttribute.h"

namespace Entities
{
	EAttribute::EAttribute(const EType& type, const std::string& name, const Tokenizer::Tokens::const_iterator& valueBegin, const Tokenizer::Tokens::const_iterator valueEnd)
		: EVariable(type, name), valueBegin(valueBegin), valueEnd(valueEnd) {}
}
