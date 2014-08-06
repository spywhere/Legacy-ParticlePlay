#include "Format.hpp"

ppFormat::ppFormat(ppIMS* ims){

}

int ppFormat::Init(const char *filename, bool stereo){
	this->filename = std::string(filename);
	this->stereo = stereo;
	return 0;
}

Sint64 ppFormat::Read(char *bufferData, Sint64 position, Sint64 size){
	return this->Read(bufferData, position, size, 0);
}

bool ppFormat::IsStereo(){
	return this->stereo;
}

std::string ppFormat::GetFileName(){
	return this->filename;
}
