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
	b2Body* boxBody;
	b2Body* circleBody;
public:
	kPlayer(ppPhysics* physics, int x, int y);
	float GetWaterLevel();
	int GetX();
	int GetY();
	void Render(SDL_Renderer* renderer);
	void Update(ppInput* input, int delta);
};

#endif
