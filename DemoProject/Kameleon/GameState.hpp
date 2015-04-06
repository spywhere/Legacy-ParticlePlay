#ifndef GAMESTATE_HEADER
#define GAMESTATE_HEADER

#include <ParticlePlay/ParticlePlay.hpp>
#include "kPlayer.hpp"
#include "Bee.hpp"
#include "Level.hpp"

class GameState {
protected:
	ppGUI* gui;
	ppPhysics* physics;
	Level* level;
	ppImage* background;
	int tx, ty;
	int debugView;
	long revealTime;
	bool triggerHeroic;
public:
	kPlayer* player;
	Bee* bee;
	void OnInit();
	void OnRender(SDL_Renderer* renderer, int delta);
	void OnUpdate(ppInput* input, int delta);
	void SetDebugView(int debugView);
};

#endif
