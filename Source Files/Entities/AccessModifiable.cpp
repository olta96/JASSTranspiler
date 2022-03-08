#include "../../Header Files/Entities/AccessModifiable.h"

namespace Entities
{
	bool AccessModifiable::getIsPublic() const
	{
		return isPublic;
	}
	
	void AccessModifiable::setPublic(const bool& isPublic)
	{
		this->isPublic = isPublic;
	}
}
