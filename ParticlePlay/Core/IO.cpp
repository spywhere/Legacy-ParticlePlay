#include "IO.hpp"

std::string ppIO::ReadFile(const char *filename){
	std::string contents;
	SDL_RWops* filePointer = SDL_RWFromFile(filename, "r");
	if(filePointer){
		char buffer[2];
		while(SDL_RWread(filePointer, buffer, 1, 1)){
			contents+=std::string(buffer);
		}
		SDL_RWclose(filePointer);
		return std::string(contents);
	}else{
		return NULL;
	}
}
