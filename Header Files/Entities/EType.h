#pragma once
#include "Entity.h"

namespace Entities
{
	class EType : public Entity
	{
	public:
		EType(const std::string& name);

		virtual bool getIsTemplate() const;

	};
}
