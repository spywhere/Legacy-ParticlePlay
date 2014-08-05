#include "Format.hpp"

ppFormat::ppFormat(ppIMS* ims){

}

int ppFormat::Init(const char *filename, bool stereo){
	this->filename = std::string(filename);
	this->filePointer = SDL_RWFromFile(this->filename.c_str(), "rb");
	this->stereo = stereo;
	return 0;
}

bool ppFormat::IsStereo(){
	return this->stereo;
}

std::string ppFormat::GetFileName(){
	return this->filename;
}
