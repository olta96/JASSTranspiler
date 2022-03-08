#pragma once

namespace Entities
{
	class StaticModifiable
	{
		bool isStatic = false;

	public:
		bool getIsStatic() const;

		void setStatic(const bool& isStatic);

	};
}
