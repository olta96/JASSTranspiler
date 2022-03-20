#include "../../Header Files/Entities/EClass.h"

namespace Entities
{
	EClass::EClass(const std::string& name) : EType(name) {}
	
	void EClass::pushTemplateTypeName(const std::string& templateTypeName)
	{
		templateTypeNames.push_back(templateTypeName);
		isTemplate = true;
	}
	
	bool EClass::getIsTemplate() const
	{
		return isTemplate;
	}

	const std::vector<std::string>& EClass::getTemplateTypeNames() const
	{
		return templateTypeNames;
	}

	const std::vector<EAttribute>& EClass::getAttributes() const
	{
		return attributes;
	}
	
	EAttribute* EClass::emplaceAttribute(const EType& type, const std::string& name, const bool& hasValue, const Tokenizer::Tokens::const_iterator& valueBegin, const Tokenizer::Tokens::const_iterator valueEnd)
	{
		attributes.emplace_back(type, name, hasValue, valueBegin, valueEnd);
		return &attributes.back();
	}
}
