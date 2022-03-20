#include "../../Header Files/Entities/EAttribute.h"

namespace Entities
{
	EAttribute::EAttribute(const EType& type, const std::string& name, const bool& hasValue, const Tokenizer::Tokens::const_iterator& valueBegin, const Tokenizer::Tokens::const_iterator valueEnd)
		: EVariable(type, name), hasValue(hasValue), valueBegin(valueBegin), valueEnd(valueEnd) {}
	
	bool EAttribute::doesHaveValue() const
	{
		return hasValue;
	}

	Tokenizer::Tokens::const_iterator EAttribute::getValueBegin() const
	{
		return valueBegin;
	}

	Tokenizer::Tokens::const_iterator EAttribute::getValueEnd() const
	{
		return valueEnd;
	}
}
