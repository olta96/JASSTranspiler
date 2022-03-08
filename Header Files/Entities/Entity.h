#pragma once
#include <string>

namespace Entities
{
	class Entity
	{
		std::string name;

	protected:
		Entity(const std::string& name);

	public:
		const std::string& getName() const;

	};
}
