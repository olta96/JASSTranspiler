#pragma once
#include "Entity.h"
#include "Returner.h"
#include "CarriesBody.h"
#include "AccessModifiable.h"
#include "StaticModifiable.h"

namespace Entities
{
	class EGetProperty : public Entity, public AccessModifiable, public StaticModifiable, public Returner, public CarriesBody
	{

	};
}
