#include "../../Header Files/Entities/EType.h"

namespace Entities
{
	EType::EType(const std::string& name) : Entity(name) {}

	bool EType::getIsTemplate() const
	{
		return false;
	}
}
