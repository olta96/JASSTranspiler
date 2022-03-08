#pragma once
#include "../../Common/Singleton.h"
#include <chrono>

namespace Utilities
{
	using namespace std::chrono;

	class HighResolutionClock : public Common::Singleton<HighResolutionClock>
	{
		friend class Singleton<HighResolutionClock>;

		const steady_clock::time_point startTime;

		HighResolutionClock();

	public:
		int getTimePoint() const;

	};
}
