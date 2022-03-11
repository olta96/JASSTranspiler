#pragma once
#include "Entity.h"
#include "AccessModifiable.h"
#include "StaticModifiable.h"
#include "EGetProperty.h"
#include "ESetProperty.h"

namespace Entities
{
	class EProperty : public Entity
	{
		const EGetProperty* getProperty = nullptr;
		const ESetProperty* setProperty = nullptr;

	public:
		EProperty(const std::string& name);

		~EProperty();
	};
}
