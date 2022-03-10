#pragma once
#include "../Tokenizer/Token.h"

namespace Entities
{
	class CarriesBody
	{
		const Tokenizer::Tokens::const_iterator bodyBegin;
		const Tokenizer::Tokens::const_iterator bodyEnd;
		std::string rendered;

	public:
		CarriesBody(const Tokenizer::Tokens::const_iterator& bodyBegin, const Tokenizer::Tokens::const_iterator& bodyEnd);

		const std::string& renderBody();
	};
}
