#ifndef LEVEL_HEADER
#define LEVEL_HEADER

#include <ParticlePlay/ParticlePlay.hpp>
#include "PhysicsObject.hpp"
#include <list>

class Level : public PhysicsObject {
protected:
	b2Body* body;
	std::list<b2Vec2> levelFog;
	std::list<b2Vec2> levelMask;
	std::list<b2Vec2> waterMask;
	ppImage* vine1;
	ppImage* vine2;
	ppImage* vine3;
	ppImage* tree1;
	ppImage* tree2;
	float reveal;
public:
	Level(ppPhysics* physics);
	void Render(SDL_Renderer* renderer);
	void RenderMask(SDL_Renderer* renderer);
	void Update(ppInput* input);
	void Reveal(long revealTime);
};

#endif
