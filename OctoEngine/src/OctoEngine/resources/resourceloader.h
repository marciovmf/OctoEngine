#pragma once
#include "resource.h"
#include <memory>

namespace octo {
	namespace resources {

		

		class ResourceLoader
		{
			public:
			ResourceLoader(){};
			virtual ~ResourceLoader(){};
		
			virtual Resource* loadResource(const char* resourceName) = 0;

		};
	}
}