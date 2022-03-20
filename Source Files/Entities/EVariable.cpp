#include "../../Header Files/Entities/EVariable.h"

namespace Entities
{
	EVariable::EVariable(const EType& type, const std::string& name) : Entity(name), type(type) {}
	
	bool EVariable::getIsConst() const
	{
		return isConst;
	}
	
	void EVariable::setConst(const bool& isConst)
	{
		this->isConst = isConst;
	}
}
