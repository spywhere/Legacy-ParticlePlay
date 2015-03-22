#ifndef KAMELEONSTATE_HEADER
#define KAMELEONSTATE_HEADER

#include <ParticlePlay/ParticlePlay.hpp>

class KameleonState : public ppState {
protected:
	ppGUI* gui;
	ppIMS* ims;
public:
	void OnInit();
	void OnRender(SDL_Renderer* renderer, int delta);
	void OnUpdate(ppInput* input, int delta);
};

#endif
