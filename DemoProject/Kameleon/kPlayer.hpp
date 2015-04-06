#ifndef KPLAYER_HEADER
#define KPLAYER_HEADER

#include <ParticlePlay/ParticlePlay.hpp>
#include "PhysicsObject.hpp"
#include "AnimateImage.hpp"

class kPlayer : public PhysicsObject {
protected:
	AnimateImage* idlePose;
	AnimateImage* runPose;
	AnimateImage* swimPose;
	AnimateImage* jumpPose;
	AnimateImage* fallPose;
	AnimateImage* currentPose;
	SDL_RendererFlip playerFlip;
	b2Body* circleBody;
	float health;
	bool isAttack;
public:
	b2Body* boxBody;
	kPlayer(ppPhysics* physics, int x, int y);
	float GetWaterLevel();
	float GetHealth();
	int GetX();
	int GetY();
	void Attack();
	void Render(SDL_Renderer* renderer);
	void Update(ppInput* input, int delta);
};

#endif
