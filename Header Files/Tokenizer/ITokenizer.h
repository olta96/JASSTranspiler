#pragma once
#include "Token.h"

namespace Tokenizer
{
	class ITokenizer
	{
	public:
		virtual const Tokens& tokenize() = 0;
	};
}
