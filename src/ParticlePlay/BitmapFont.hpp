#ifndef BITMAP_FONT_HEADER
#define BITMAP_FONT_HEADER

#include "Includes.hpp"

class ppBitmapFont{
	protected:
		SDL_Renderer* renderer;
		SDL_Surface* bitmap;
		SDL_Texture* texture;
		SDL_Rect chars[256];
		int spacing;
		int linespacing;
		int space;
		int line;
		Uint32 GetPixel(int x, int y, SDL_Surface* surface);
		void RenderSurface(int x, int y, SDL_Texture* texture, SDL_Rect* offset);
	public:
		ppBitmapFont(SDL_Surface* surface);
		void SetSpacing(int spacing);
		void SetLineSpacing(int spacing);
		void Render(int x, int y, const char* text, SDL_Renderer* renderer);
};

#endif
