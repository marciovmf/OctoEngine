#pragma once


namespace octo {

	namespace resources {

		class Resource
		{
		protected:
			const char* const m_Name;
		public:
			Resource(const char * const resourceName);
			// Returns the unique name of this resource
			inline const char* const getName(){ return m_Name; }
			// Returns this resource a UNIQUE IDENTIFIER for this resource TYPE.
			virtual ~Resource();		
		};

	}
}