#ifndef TILE_HEADER
#define TILE_HEADER

#include "../ParticlePlay/ParticlePlay.hpp"
#include "Spritesheet.hpp"

class Spritesheet;
class Tile {
protected:
	Spritesheet* spritesheet;
	int xOffset;
	int yOffset;
	float scale;
public:
	Tile(Spritesheet* spritesheet, int xOffset, int yOffset, float scale);
	void Render(SDL_Renderer *renderer, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip);
	void Render(SDL_Renderer *renderer, int x, int y, double angle, SDL_RendererFlip flip);
	void Render(SDL_Renderer *renderer, int x, int y, double angle, SDL_Point* center);
	void Render(SDL_Renderer *renderer, int x, int y, SDL_RendererFlip flip);
	void Render(SDL_Renderer *renderer, int x, int y, double angle);
	void Render(SDL_Renderer *renderer, int x, int y);
	int GetTileWidth();
	int GetTileHeight();
	int GetWidth();
	int GetHeight();
};

#endif
