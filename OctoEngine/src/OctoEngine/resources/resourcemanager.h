#pragma once
#include <iostream>
#include <typeinfo>
#include <map>
#include <memory>
#include "resourceloader.h"
#include "resource.h"

namespace octo {
	namespace resources {

		//class Resource;

		class ResourceManager
		{
		// Public Methods
		public:
			// Gets a resource of type T identifyed by the name in resourceName
			template <typename T> static std::shared_ptr<T> get(const char* resourceName);
			// Try to release a resource identifyed by the name in resourceName
			void Release(const char* resourceName);

			// Register a Loader class for a given type. Returns false if there is already a loader getistered for the same type;
			template <typename T> bool static registerLoader(const ResourceLoader* loader);

			// Returns true it there is a loader set up for the given type. False otherwise.
			template <typename T> bool hasLoaderForType() const;

		// Private Members
		private:
			std::map<const char*, std::shared_ptr<Resource>> m_Resources;
			std::map<const std::size_t, octo::resources::ResourceLoader* > m_Loaders;
			static ResourceManager* m_Instance;

		// Private Methods
		public:
			ResourceManager();
			~ResourceManager();
			static void initialize();
			static void Destroy();

			template <typename T> static bool registerLoader(ResourceLoader* const loader);
			template <typename T> static std::shared_ptr<T> ResourceManager::get(const char* resourceName);
			//static inline ResourceManager& getInstance() { return *ResourceManager::m_Instance; }
		};

		template <typename T>
		bool ResourceManager::registerLoader(ResourceLoader* const loader)
		{
			// Get the resource type's hash 
			std::size_t hash = typeid(T).hash_code();
			
			// check if there is already a loader registered for this type
			std::map<const std::size_t, octo::resources::ResourceLoader* >::iterator it =
				m_Instance->m_Loaders.find(hash);

			// Return FALSE if there is already a loader for this type.
			if (it != m_Instance->m_Loaders.end())
				return false;
			
			// Add the loader to the list
			m_Instance->m_Loaders[hash] = loader;

			return true;
		}

		// Gets a resource of type T identifyed by the name in resourceName
		template <typename T>
		std::shared_ptr<T> ResourceManager::get(const char* resourceName)
		{
			// Return a cached version of this resource, if avaliable
			auto resIter = m_Instance->m_Resources.find(resourceName);
			if (resIter != m_Instance->m_Resources.end())
			{
				//std::cout << "Returning cached resource for:" << resourceName << std::endl;
				return std::dynamic_pointer_cast<T>(resIter->second);
			}

			// There is no cached version of the resource!
			// Get the resource type's unique hash
			std::size_t hash = typeid(T).hash_code();

			// check if there is already a loader registered for this type
			auto it = m_Instance->m_Loaders.find(hash);

			//TODO: Log that an atempt to load a resource with lo loader registered was made
			// Return nullptr if there is no loader for this type.
			if (it == m_Instance->m_Loaders.end())
				return nullptr;

			// Loads the resource throu the registered loader
			Resource* resourcePtr = ((*it).second)->loadResource(resourceName);
			std::shared_ptr<T> sharedResPtr = std::make_shared<T>(*static_cast<T*>(resourcePtr));

			// Add the newly loaded resource to the cache
			m_Instance->m_Resources[resourceName] = sharedResPtr;

			//std::cout << "Returning just loaded resource for:" << resourceName << std::endl;

			// Return the resource
			return sharedResPtr;
			
		}
	}
}