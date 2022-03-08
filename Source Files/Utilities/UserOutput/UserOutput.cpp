#include "../../../Header Files/Utilities/UserOutput/UserOutput.h"
#include "../../../Header Files/Utilities/HighResolutionClock/HighResolutionClock.h"
#include <iostream>

namespace Utilities
{
	using std::cout;
	using std::cerr;


	UserOutput::UserOutput() {}

	
	void UserOutput::log(const std::string& message) const { log(message, "\n"); }
	void UserOutput::log(const std::string& message, const std::string& end) const
	{
		cout << message << end;
	}


	void UserOutput::warn(const std::string& message) { warn(message, "\n\n"); }
	void UserOutput::warn(const std::string& message, const std::string& end)
	{
		cerr << "\nWarning: " << message << end;
		++warnings;
	}

	
	void UserOutput::error(const std::string& message) const { error(message, "\n\n"); }
	void UserOutput::error(const std::string& message, const std::string& end) const
	{
		cerr << "\nError: " << message << end;
	}


	void UserOutput::logTimePoint() const { logTimePoint("\n"); }
	void UserOutput::logTimePoint(const std::string& end) const
	{
		const HighResolutionClock& highResolutionClock = HighResolutionClock::getInstance();

		cout << std::to_string(highResolutionClock.getTimePoint()) << " ms" << end;
	}


	const int& UserOutput::getWarnings() const
	{
		return warnings;
	}
}
