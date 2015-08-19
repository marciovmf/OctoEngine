#ifndef OCTOENGINE_H
#define OCTOENGINE_H

#include <iostream>

#ifdef _DEBUG
#define OCTO_ASSERTION 1
#endif

#ifdef OCTO_ASSERTION
#define OCTO_ASSERT(expr, text) if ( !expr ) { std::cerr << "["<< __FILE__ << ":" << __LINE__ <<  "] - Assertion Failed:" << ":" << text << std::endl; _asm int 3 }
#else
#define OCTO_ASSERT(expr, text)
#endif

#endif