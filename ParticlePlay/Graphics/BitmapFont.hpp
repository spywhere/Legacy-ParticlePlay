#ifndef BITMAP_FONT_HEADER
#define BITMAP_FONT_HEADER

#include <ParticlePlay/Includes.hpp>
#include <ParticlePlay/Graphics/Graphics.hpp>
#include <ParticlePlay/Graphics/Image.hpp>

class ppBitmapFont{
	protected:
		SDL_Surface* bitmap;
		SDL_Rect chars[256];
		ppImage* image;
		int spacing;
		int linespacing;
		int space;
		int line;
		Uint32 GetPixel(int x, int y, SDL_Surface* surface);
	public:
		ppBitmapFont(SDL_Surface* surface);
		void SetSpacing(int spacing);
		void SetLineSpacing(int spacing);
		void Render(int x, int y, const char* text, ppGraphics* graphics);
};

#endif
