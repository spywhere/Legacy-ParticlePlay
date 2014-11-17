#ifndef IMAGE_HEADER
#define IMAGE_HEADER

#include "../Includes.hpp"

class ppImage{
protected:
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Renderer* renderer;
public:
	ppImage(SDL_Surface *surface);
	ppImage(const char *filename);

	void Render(SDL_Renderer *renderer, int x, int y, int xOffset, int yOffset, int width, int height);
	void Render(SDL_Renderer *renderer, int x, int y, int width, int height);
	void Render(SDL_Renderer *renderer, int x, int y);
	int GetWidth();
	int GetHeight();
};

#endif
