#pragma once
#include "EVariable.h"
#include "AccessModifiable.h"
#include "StaticModifiable.h"
#include "../Tokenizer/Token.h"

namespace Entities
{
	class EAttribute : public EVariable, public AccessModifiable, public StaticModifiable
	{
		const Tokenizer::Tokens::const_iterator valueBegin;
		const Tokenizer::Tokens::const_iterator valueEnd;

	public:
		EAttribute(const EType& type, const std::string& name, const Tokenizer::Tokens::const_iterator& valueBegin, const Tokenizer::Tokens::const_iterator valueEnd);

	};
}
