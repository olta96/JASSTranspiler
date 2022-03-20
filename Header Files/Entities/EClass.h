#pragma once
#include <vector>
#include "EType.h"
#include "EAttribute.h"
#include "EProperty.h"
#include "EMethod.h"
#include "EOperator.h"

namespace Entities
{
	class EClass : public EType
	{
		std::vector<EAttribute> attributes;
		std::vector<EProperty> properties;
		std::vector<EMethod> methods;
		std::vector<EOperator> operators;
		bool isTemplate = false;
		std::vector<std::string> templateTypeNames;
		const EMethod* constructor = nullptr;
		const EMethod* destructor = nullptr;

	public:
		EClass(const std::string& name);

		void pushTemplateTypeName(const std::string& templateTypeName);

		bool getIsTemplate() const override;

		const std::vector<std::string>& getTemplateTypeNames() const;

		const std::vector<EAttribute>& getAttributes() const;

		EAttribute* emplaceAttribute(const EType& type, const std::string& name, const bool& hasValue, const Tokenizer::Tokens::const_iterator& valueBegin, const Tokenizer::Tokens::const_iterator valueEnd);

	};
}
