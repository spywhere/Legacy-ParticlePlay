#ifndef LEVEL_HEADER
#define LEVEL_HEADER

#include <ParticlePlay/ParticlePlay.hpp>
#include "PhysicsObject.hpp"

class Level : public PhysicsObject {
protected:
	b2Body* body;
public:
	Level(ppPhysics* physics);
	void Render(SDL_Renderer* renderer);
	void Update(ppInput* input);
};

#endif
