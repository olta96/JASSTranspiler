#include "../../../Header Files/Utilities/HighResolutionClock/HighResolutionClock.h"
#include <chrono>

namespace Utilities
{
	HighResolutionClock::HighResolutionClock() : startTime(high_resolution_clock::now()) {}

	int HighResolutionClock::getTimePoint() const
	{
		return duration_cast<milliseconds>(high_resolution_clock::now() - startTime).count();
	}

}
