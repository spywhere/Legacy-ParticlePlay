#ifndef COLOR_HEADER
#define COLOR_HEADER

#include "Includes.hpp"

class ppColor{
protected:
	Uint32 color;
public:
	ppColor() : ppColor(0xff000000) {}
	ppColor(float r, float g, float b) : ppColor(r, g, b, 1.0f) {}
	ppColor(float r, float g, float b, float a);
	ppColor(Uint8 r, Uint8 g, Uint8 b) : ppColor(r, g, b, 0xff) {}
	ppColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	ppColor(Uint32 color);
	Uint32 GetColor();
	Uint8 GetR();
	Uint8 GetG();
	Uint8 GetB();
	Uint8 GetA();
	float GetRf();
	float GetGf();
	float GetBf();
	float GetAf();
};

#endif
