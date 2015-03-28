#ifndef KPLAYER_HEADER
#define KPLAYER_HEADER

#include <ParticlePlay/ParticlePlay.hpp>
#include "PhysicsObject.hpp"

class kPlayer : public PhysicsObject {
protected:
	b2Body* boxBody;
	b2Body* circleBody;
	int px, py;
public:
	kPlayer(ppPhysics* physics, int x, int y);
	float GetWaterLevel();
	void Render(SDL_Renderer* renderer);
	void Update(ppInput* input);
};

#endif
