#include "resourcemanager.h"

namespace octo {
	namespace resources {

		ResourceManager* ResourceManager::m_Instance = nullptr;

		// Public Methods

		// Try to release a resource identifyed by the name in resourceName
		void ResourceManager::Release(const char* resourceName)	{ }

		// Returns true it there is a loader set up for the given type. False otherwise.
		template <typename T> 
		bool ResourceManager::hasLoaderForType() const
		{
			return (m_Loaders.find(typeid(T)) != m_Loaders.end());
		}

		void ResourceManager::initialize()
		{
			ResourceManager::m_Instance = new ResourceManager();
		}

		void ResourceManager::Destroy()
		{
			delete ResourceManager::m_Instance;
		}

		ResourceManager::ResourceManager()
		{

		}

		ResourceManager::~ResourceManager()
		{

		}
	}
}