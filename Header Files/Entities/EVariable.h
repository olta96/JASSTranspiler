#pragma once
#include "Entity.h"
#include "EType.h"

namespace Entities
{
	class EVariable : public Entity
	{
		const EType& type;

	public:
		EVariable(const EType& type, const std::string& name);

	};
}
