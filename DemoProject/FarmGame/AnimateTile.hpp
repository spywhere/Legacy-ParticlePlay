#ifndef ANIMATETILE_HEADER
#define ANIMATETILE_HEADER

#include <ParticlePlay/ParticlePlay.hpp>
#include "Spritesheet.hpp"
#include "Tile.hpp"

class AnimateTile : public Tile {
protected:
	int currentFrame;
	int frameTime;
	int* xOffsets;
	int* yOffsets;
	int animationSize;
	int animationDelay;
public:
	AnimateTile(Spritesheet* spritesheet, int* xOffsets, int* yOffsets, int animationSize, int animationDelay, float scale);
	void Render(SDL_Renderer *renderer, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip);
	void Update(ppInput* input, int delta);
};

#endif
