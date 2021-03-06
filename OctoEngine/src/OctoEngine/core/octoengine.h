#ifndef OCTOENGINE_H
#define OCTOENGINE_H

#include <iostream>

#if defined _DEBUG ||_DEBUG_ || _DEBUG_ || __DEBUG__
#define DEBUG
#define OCTO_ASSERTION 1
#endif


#ifdef OCTO_ASSERTION
#define OCTO_ASSERT(expr, text) if ( !expr ) { std::cerr << "["<< __FILE__ << ":" << __LINE__ <<  "] - Assertion Failed:" << ":" << text << std::endl; _asm int 3 }
#else
#define OCTO_ASSERT(expr, text)
#endif
#include <glm/detail/type_vec3.hpp>


namespace octo
{
	namespace graphics
	{
		class Mesh;
	}
}

//A type for holding the instance id of an object guaranteed to be unique.
typedef long long INSTANCEID;

namespace octo
{
	namespace resources
	{
		class Resource;
		//typedef Resource* (*RESOURCELOADERFUNCPTR)(const char*);
		//typedef unsigned int HANDLE_RESOURCE;
		/*typedef std::shared_ptr<graphics::Shader> ShaderPtr;
		typedef std::shared_ptr<graphics::Texture> TexturePtr;
		typedef std::shared_ptr<graphics::Mesh> MeshPtr;*/
	}


	inline void print(const char* text)
	{
		std::cout << text << std::endl;
	}

	inline void print(const glm::vec3& v)
	{
		std::cout << "(" << v.x << "," << v.y << "," << v.z << ")" << std::endl;
	}
}
#endif
