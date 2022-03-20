#pragma once
#include "Entity.h"
#include "EType.h"

namespace Entities
{
	class EVariable : public Entity
	{
		const EType& type;
		bool isConst = false;

	public:
		EVariable(const EType& type, const std::string& name);

		bool getIsConst() const;

		void setConst(const bool& isConst);

	};
}
