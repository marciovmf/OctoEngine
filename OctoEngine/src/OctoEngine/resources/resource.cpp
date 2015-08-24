#include "resource.h"

namespace octo {

	namespace resources {

		Resource::Resource(const char * const resourceName) 
			: octo::Object(), m_Name(resourceName)
		{}

		Resource::~Resource()
		{}

	}
}