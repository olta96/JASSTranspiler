#pragma once
#include "Entity.h"
#include "AccessModifiable.h"
#include "StaticModifiable.h"

namespace Entities
{
	class EProperty : public Entity, public AccessModifiable, public StaticModifiable
	{
	public:
		EProperty(const std::string& name);

	};
}
