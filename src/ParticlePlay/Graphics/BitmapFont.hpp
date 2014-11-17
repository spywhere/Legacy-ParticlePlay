#ifndef BITMAP_FONT_HEADER
#define BITMAP_FONT_HEADER

#include "../Includes.hpp"
#include "Image.hpp"

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
		void Render(int x, int y, const char* text, SDL_Renderer* renderer);
};

#endif
