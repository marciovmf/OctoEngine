#include "exception.h"

namespace octo
{
	Exception::Exception(const std::string& message)
		: m_Message(message)
	{
	}

	Exception::~Exception()
	{
	}

	const std::string& Exception::getMessage() const
	{
		return m_Message;
	}
}
