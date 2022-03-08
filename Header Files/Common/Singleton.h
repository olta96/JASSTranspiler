#pragma once

namespace Common
{
	template<typename TChild>
	class Singleton
	{
	protected:
		Singleton() {}

	public:
		static TChild& getInstance()
		{
			static TChild instance;
			return instance;
		}

		Singleton(Singleton const&) = delete;

		Singleton& operator=(Singleton const&) = delete;

	};
}
