#ifndef OCTO_UTILS_H_
#define OCTO_UTILS_H_
#include <memory>
#include <string>
#include <fstream>
#include <sstream>

namespace octo
{
	// loads the conte
	inline std::unique_ptr<std::string> LoadFile(const char* fileName)
	{
		std::unique_ptr <std::string> result(nullptr);

		try {
			std::ifstream file;
			file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			file.open(fileName);
			std::stringstream source;

			source << file.rdbuf();
			file.close();
			result = std::make_unique<std::string>(source.str());
		}
		catch (std::exception e)
		{
			std::cerr << "[ERROR]:" << fileName << e.what() << std::endl;
		}
		return result;
	}
}

#endif