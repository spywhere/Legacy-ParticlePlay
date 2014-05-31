#include "Color.hpp"

ppColor::ppColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
	this->color = (a<<24)|(r<<16)|(g<<8)|b;
}

ppColor::ppColor(float r, float g, float b, float a){
	int aa = a*255;
	int rr = r*255;
	int gg = g*255;
	int bb = b*255;
	this->color = (aa<<24)|(rr<<16)|(gg<<8)|bb;
}

ppColor::ppColor(Uint32 color){
	this->color = color;
}

Uint32 ppColor::GetColor(){
	return this->color;
}

Uint8 ppColor::GetR(){
	return (this->color>>16)&0xff;
}

Uint8 ppColor::GetG(){
	return (this->color>>8)&0xff;
}

Uint8 ppColor::GetB(){
	return this->color&0xff;
}

Uint8 ppColor::GetA(){
	return (this->color>>24)&0xff;
}

float ppColor::GetRf(){
	return this->GetR()/255.0f;
}

float ppColor::GetGf(){
	return this->GetG()/255.0f;
}

float ppColor::GetBf(){
	return this->GetB()/255.0f;
}

float ppColor::GetAf(){
	return this->GetA()/255.0f;
}
