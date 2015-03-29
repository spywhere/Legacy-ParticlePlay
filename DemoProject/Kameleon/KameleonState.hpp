#ifndef KAMELEONSTATE_HEADER
#define KAMELEONSTATE_HEADER

#include <ParticlePlay/ParticlePlay.hpp>
#include "GameState.hpp"

class KameleonState : public ppState {
protected:
	ppGUI* gui;
	GameState* gameState;
public:
	int debugView;
	void OnInit();
	void OnRender(SDL_Renderer* renderer, int delta);
	void OnUpdate(ppInput* input, int delta);
};

#endif
