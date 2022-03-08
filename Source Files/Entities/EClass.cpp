#include "../../Header Files/Entities/EClass.h"

namespace Entities
{
	EClass::EClass(const std::string& name) : Entity(name) {}
	
	void EClass::pushTemplateTypeName(const std::string& templateTypeName)
	{
		templateTypeNames.push_back(templateTypeName);
		isTemplate = true;
	}
	
	bool EClass::getIsTemplate() const
	{
		return isTemplate;
	}
}
