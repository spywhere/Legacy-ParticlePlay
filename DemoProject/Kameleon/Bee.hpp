#ifndef BEE_HEADER
#define BEE_HEADER

#include <ParticlePlay/ParticlePlay.hpp>
#include "PhysicsObject.hpp"
#include "AnimateImage.hpp"

class Bee : public PhysicsObject {
protected:
	AnimateImage* flyPose;
	SDL_RendererFlip playerFlip;
	b2Vec2 trackingPoint;
	bool tracking;
	float health;
public:
	b2Body* body;
	Bee(ppPhysics* physics, int x, int y);
	void Render(SDL_Renderer* renderer);
	void Update(ppInput* input, int delta);
	void SetTracking(b2Vec2 point);
	void StartTracking();
	void Attack();
	float GetTrackingLength();
	float GetHealth();
};

#endif
