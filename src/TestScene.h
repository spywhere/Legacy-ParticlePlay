#ifndef TESTSCENE_HEADER
#define TESTSCENE_HEADER

#include "ParticlePlay/Includes.h"
#include "ParticlePlay/GUI/GUI.h"
#include "ParticlePlay/State.h"
#include "ParticlePlay/BitmapFont.h"
#include "ParticlePlay/Input.h"

class TestScene : public ppState{
protected:
	ppBitmapFont* font;
	ppGUI* gui;
	int posx, posy;
public:
	void OnInit();
	void OnRender(SDL_Renderer* renderer, int delta);
	void OnUpdate(ppInput* input, int delta);
};

#endif
