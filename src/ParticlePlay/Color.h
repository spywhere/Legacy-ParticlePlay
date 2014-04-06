#ifndef COLOR_HEADER
#define COLOR_HEADER

#include "Includes.h"

class ppColor{
private:
	Uint32 color;
public:
	ppColor();
	ppColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	ppColor(Uint8 r, Uint8 g, Uint8 b);
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