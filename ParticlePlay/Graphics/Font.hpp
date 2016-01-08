#ifndef FONT_HEADER
#define FONT_HEADER

#include <ParticlePlay/Graphics/Graphics.hpp>
#include <ParticlePlay/Graphics/Types.hpp>

class ppFont {
public:
	virtual void Render(int x, int y, const char* text, ppGraphics* graphics)=0;
	virtual ppSize GetRenderSize(const char* text)=0;
};

#endif
