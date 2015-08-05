#include "resourcemanager.h"

namespace octo {
	namespace resources {

		ResourceManager* ResourceManager::m_Instance = nullptr;

		ResourceManager::ResourceManager(){ }

		void ResourceManager::initialize() 
		{
			ResourceManager::m_Instance = new ResourceManager();
		}

		void ResourceManager::Destroy()
		{
			delete ResourceManager::m_Instance;
		}

		bool ResourceManager::ReleaseResource(ResourcePtr& resourcePtr)
		{
			
			if (ResourceManager::m_Instance->m_Resources.end() == 
				ResourceManager::m_Instance->m_Resources.find((*resourcePtr).getName()))
				return false;
			
			const char* name = resourcePtr->getName();
			resourcePtr.reset();
			if (ResourceManager::m_Instance->m_Resources[name].unique())
			{
				ResourceManager::m_Instance->m_Resources.erase(name);
				return true;
			}
			
			return false;
		}

		ResourceManager::~ResourceManager()
		{
			m_Loaders.clear();
			m_Resources.clear();
		}
	}
}