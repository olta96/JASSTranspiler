#pragma once
#include "Entity.h"
#include "AccessModifiable.h"
#include "StaticModifiable.h"

namespace Entities
{
	class EOperator : public Entity, public AccessModifiable, public StaticModifiable
	{
	public:
		EOperator(const std::string& name);

	};
}
