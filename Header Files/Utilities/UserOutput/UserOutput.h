#pragma once
#include <string>
#include "../../Common/Singleton.h"

namespace Utilities
{
	class UserOutput : public Common::Singleton<UserOutput>
	{
		friend class Singleton<UserOutput>;

		int warnings = 0;

		UserOutput();

	public:
		void log(const std::string& message) const;

		void log(const std::string& message, const std::string& end) const;

		void warn(const std::string& message);

		void warn(const std::string& message, const std::string& end);

		void error(const std::string& message) const;

		void error(const std::string& message, const std::string& end) const;

		void logTimePoint() const;

		void logTimePoint(const std::string& end) const;

		const int& getWarnings() const;

	};
}
