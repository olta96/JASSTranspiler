#pragma once
#include "Entity.h"
#include "CarriesBody.h"
#include "AccessModifiable.h"
#include "StaticModifiable.h"

namespace Entities
{
	class ESetProperty : public Entity, public AccessModifiable, public StaticModifiable, public CarriesBody
	{

	};
}
