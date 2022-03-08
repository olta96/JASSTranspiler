#pragma once

namespace Entities
{
	class AccessModifiable
	{
		bool isPublic = false;

	public:
		bool getIsPublic() const;

		void setPublic(const bool& isPublic);

	};
}
