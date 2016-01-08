#ifndef BITMAP_FONT_HEADER
#define BITMAP_FONT_HEADER

#include <ParticlePlay/Includes.hpp>
#include <ParticlePlay/Graphics/Types.hpp>
#include <ParticlePlay/Graphics/Font.hpp>
#include <ParticlePlay/Graphics/Graphics.hpp>
#include <ParticlePlay/Graphics/Image.hpp>

class ppBitmapFont : public ppFont {
// protected:
public:
	ppBitmapFont(const char* filename);
	void Render(int x, int y, const char* text, ppGraphics* graphics);
	ppSize GetRenderSize(const char* text);
};

#endif
