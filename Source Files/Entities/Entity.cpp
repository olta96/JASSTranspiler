#include "../../Header Files/Entities/Entity.h"

namespace Entities
{
	Entity::Entity(const std::string& name) : name(name) {}
	
	const std::string& Entity::getName() const
	{
		return name;
	}
}
