#ifndef CHICKEN_HEADER
#define CHICKEN_HEADER

#include <ParticlePlay/ParticlePlay.hpp>
#include "Entity.hpp"
#include "Spritesheet.hpp"

class Chicken : public Entity {
protected:
	int angle;
public:
	Chicken(Spritesheet* spritesheet, int startX, int startY);
	void Render(ppGraphics* graphics);
	void Update(ppInput* input, int delta);
};

#endif
