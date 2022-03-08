#include "../../Header Files/Entities/StaticModifiable.h"

namespace Entities
{
	bool StaticModifiable::getIsStatic() const
	{
		return isStatic;
	}
	
	void StaticModifiable::setStatic(const bool& isStatic)
	{
		this->isStatic = isStatic;
	}
}
