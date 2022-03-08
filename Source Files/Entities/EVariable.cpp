#include "../../Header Files/Entities/EVariable.h"

namespace Entities
{
	EVariable::EVariable(const std::string& name, const EType& type) : Entity(name), type(type) {}
}
