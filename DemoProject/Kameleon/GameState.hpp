#ifndef GAMESTATE_HEADER
#define GAMESTATE_HEADER

#include <ParticlePlay/ParticlePlay.hpp>
#include "kPlayer.hpp"

class GameState {
protected:
	ppPhysics* physics;
	kPlayer* player;
public:
	void OnInit();
	void OnRender(SDL_Renderer* renderer, int delta);
	void OnUpdate(ppInput* input, int delta);
};

#endif
