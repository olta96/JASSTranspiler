#include "../../Header Files/Entities/EProperty.h"

namespace Entities
{
	EProperty::EProperty(const std::string& name) : Entity(name) {}

	EProperty::~EProperty()
	{
		delete getProperty;
		delete setProperty;
	}
}
