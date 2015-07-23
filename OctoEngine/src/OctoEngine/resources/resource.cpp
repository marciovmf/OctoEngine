#include "resource.h"

namespace octo {

	namespace resources {

		Resource::Resource(const char * const resourceName) : m_Name(resourceName)
		{}

		Resource::~Resource()
		{}

	}
}