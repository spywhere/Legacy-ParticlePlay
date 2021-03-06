#ifndef IMAGE_HEADER
#define IMAGE_HEADER

#include <ParticlePlay/Includes.hpp>

class ppGraphics;
class ppImage{
protected:
	SDL_Surface* surface;
	SDL_Texture* texture;
	ppGraphics* graphics;
public:
	ppImage(SDL_Surface *surface);
	ppImage(const char *filename);

	static SDL_Point* MakePoint(int x, int y);
	static SDL_Point* NO_CENTER;
	static SDL_RendererFlip NO_FLIP;
	static SDL_RendererFlip FLIP_HORIZONTAL;
	static SDL_RendererFlip FLIP_VERTICAL;
	static SDL_RendererFlip FLIP_ALL;

	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, int sw, int sh, int dw, int dh, double angle, SDL_Point* center, SDL_RendererFlip flip);
	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, int sw, int sh, int dw, int dh, double angle, SDL_RendererFlip flip);
	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, int sw, int sh, int dw, int dh, double angle, SDL_Point* center);
	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, int sw, int sh, int dw, int dh, SDL_RendererFlip flip);
	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, int sw, int sh, int dw, int dh, double angle);
	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, int sw, int sh, int dw, int dh);

	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, int width, int height, double angle, SDL_Point* center, SDL_RendererFlip flip);
	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, int width, int height, double angle, SDL_RendererFlip flip);
	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, int width, int height, double angle, SDL_Point* center);
	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, int width, int height, SDL_RendererFlip flip);
	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, int width, int height, double angle);
	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, int width, int height);

	void Render(ppGraphics* graphics, int x, int y, int width, int height, double angle, SDL_Point* center, SDL_RendererFlip flip);
	void Render(ppGraphics* graphics, int x, int y, int width, int height, double angle, SDL_RendererFlip flip);
	void Render(ppGraphics* graphics, int x, int y, int width, int height, double angle, SDL_Point* center);
	void Render(ppGraphics* graphics, int x, int y, int width, int height, SDL_RendererFlip flip);
	void Render(ppGraphics* graphics, int x, int y, int width, int height, double angle);
	void Render(ppGraphics* graphics, int x, int y, int width, int height);

	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, float sw, float sh, float dw, float dh, double angle, SDL_Point* center, SDL_RendererFlip flip);
	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, float sw, float sh, float dw, float dh, double angle, SDL_RendererFlip flip);
	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, float sw, float sh, float dw, float dh, double angle, SDL_Point* center);
	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, float sw, float sh, float dw, float dh, SDL_RendererFlip flip);
	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, float sw, float sh, float dw, float dh, double angle);
	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, float sw, float sh, float dw, float dh);

	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, float width, float height, double angle, SDL_Point* center, SDL_RendererFlip flip);
	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, float width, float height, double angle, SDL_RendererFlip flip);
	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, float width, float height, double angle, SDL_Point* center);
	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, float width, float height, SDL_RendererFlip flip);
	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, float width, float height, double angle);
	void Render(ppGraphics* graphics, int sx, int sy, int dx, int dy, float width, float height);

	void Render(ppGraphics* graphics, int x, int y, float width, float height, double angle, SDL_Point* center, SDL_RendererFlip flip);
	void Render(ppGraphics* graphics, int x, int y, float width, float height, double angle, SDL_RendererFlip flip);
	void Render(ppGraphics* graphics, int x, int y, float width, float height, double angle, SDL_Point* center);
	void Render(ppGraphics* graphics, int x, int y, float width, float height, SDL_RendererFlip flip);
	void Render(ppGraphics* graphics, int x, int y, float width, float height, double angle);
	void Render(ppGraphics* graphics, int x, int y, float width, float height);

	void Render(ppGraphics* graphics, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip);
	void Render(ppGraphics* graphics, int x, int y, double angle, SDL_RendererFlip flip);
	void Render(ppGraphics* graphics, int x, int y, double angle, SDL_Point* center);
	void Render(ppGraphics* graphics, int x, int y, SDL_RendererFlip flip);
	void Render(ppGraphics* graphics, int x, int y, double angle);
	void Render(ppGraphics* graphics, int x, int y);

	int GetWidth();
	int GetHeight();
};

#endif
