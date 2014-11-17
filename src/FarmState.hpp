#ifndef FARMSTATE_HEADER
#define FARMSTATE_HEADER

#include "ParticlePlay/ParticlePlay.hpp"

class FarmState : public ppState {
protected:
	ppGraphics* graphics;
	ppGUI* gui;
	ppIMS* ims;
	ppImage* image;
public:
	void OnInit();
	void OnRender(SDL_Renderer* renderer, int delta);
	void OnUpdate(ppInput* input, int delta);
};

#endif
