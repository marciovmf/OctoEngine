#include "object.h"

namespace octo
{
	INSTANCEID Object::m_instancePool = 0;

	Object::Object()
	{
		m_InstanceId = m_instancePool++;
	}

	Object::~Object()
	{
	}

	INSTANCEID Object::getInstanceID()
	{
		return m_InstanceId;
	}
}
