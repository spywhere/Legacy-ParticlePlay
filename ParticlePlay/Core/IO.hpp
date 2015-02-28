#ifndef IO_HEADER
#define IO_HEADER

#include <string>
#include <ParticlePlay/Includes.hpp>

class ppIO{
public:
	std::string ReadFile(const char *filename);
};

#endif
