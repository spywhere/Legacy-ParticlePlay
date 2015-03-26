#ifndef FPLAYER_HEADER
#define FPLAYER_HEADER

#include <ParticlePlay/ParticlePlay.hpp>
#include "Entity.hpp"
#include "Spritesheet.hpp"

class Player : public Entity {
public:
	Player(Spritesheet* spritesheet, int startX, int startY);
	void Render(SDL_Renderer* renderer);
	void Update(ppInput* input, int delta);
};

#endif
