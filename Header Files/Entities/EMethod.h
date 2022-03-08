#pragma once
#include "Entity.h"
#include "AccessModifiable.h"
#include "EVariable.h"
#include <vector>
#include "StaticModifiable.h"

namespace Entities
{
	class EMethod : public Entity, public AccessModifiable, public StaticModifiable
	{
		std::vector<EVariable> locals;

	public:
		EMethod(const std::string& name);

	};
}
