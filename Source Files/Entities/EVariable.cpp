#include "../../Header Files/Entities/EVariable.h"

namespace Entities
{
	EVariable::EVariable(const EType& type, const std::string& name) : Entity(name), type(type) {}
}
