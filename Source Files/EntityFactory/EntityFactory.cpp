#include "../../Header Files/EntityFactory/EntityFactory.h"

namespace EntityFactory
{
	using namespace Tokenizer::TokenConstants;

	EntityFactory::EntityFactory()
		:
			voidType(LIT_T_VOID),
			thistypeType(LIT_T_THISTYPE)
	{
		types.push_back(&voidType);
		types.push_back(&thistypeType);
	}
}
