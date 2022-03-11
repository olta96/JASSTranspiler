#pragma once

namespace EntityFactory
{
	class IEntityFactory
	{
	public:
		virtual void buildEntities() = 0;
	};
}
