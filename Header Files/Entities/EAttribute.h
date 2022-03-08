#pragma once
#include "EVariable.h"
#include "AccessModifiable.h"
#include "StaticModifiable.h"

namespace Entities
{
	class EAttribute : public EVariable, public AccessModifiable, public StaticModifiable
	{
	public:
		EAttribute(const std::string& name, const EType& type);

	};
}
