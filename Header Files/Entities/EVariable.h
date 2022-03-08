#pragma once
#include "Entity.h"
#include "EType.h"

namespace Entities
{
	class EVariable : public Entity
	{
		const EType& type;

	public:
		EVariable(const std::string& name, const EType& type);

	};
}
