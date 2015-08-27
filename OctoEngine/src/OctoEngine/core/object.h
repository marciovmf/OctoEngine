#pragma once
#include "octoengine.h"

namespace octo
{
	typedef unsigned int HANDLE_RESOURCE;

	class Object
	{
	private:
		static INSTANCEID m_instancePool;
		INSTANCEID m_InstanceId;
	public:
		Object();
		virtual ~Object();
		
		//The instance id of an object is always guaranteed to be unique.
		INSTANCEID getInstanceID();
	};
}

