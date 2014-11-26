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
	float clipX;
	float clipY;
public:
	Tile(Spritesheet* spritesheet, int xOffset, int yOffset, float scale);
	virtual void Render(SDL_Renderer *renderer, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip);
	virtual void Render(SDL_Renderer *renderer, int x, int y, double angle, SDL_RendererFlip flip);
	virtual void Render(SDL_Renderer *renderer, int x, int y, double angle, SDL_Point* center);
	virtual void Render(SDL_Renderer *renderer, int x, int y, SDL_RendererFlip flip);
	virtual void Render(SDL_Renderer *renderer, int x, int y, double angle);
	virtual void Render(SDL_Renderer *renderer, int x, int y);
	virtual void Update(ppInput* input, int delta);
	void SetClip(float cx, float cy);
	int GetTileWidth();
	int GetTileHeight();
	int GetWidth();
	int GetHeight();
};

#endif
