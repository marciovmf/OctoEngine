#pragma once
#include <string>

namespace octo
{
	class Exception
	{
	private:
		const std::string m_Message;
	public:
		Exception(const std::string& message);
		virtual ~Exception();
		const std::string& getMessage() const;
	};
}
