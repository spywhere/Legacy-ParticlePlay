#ifndef TESTSCENE_HEADER
#define TESTSCENE_HEADER

#include "ParticlePlay/Includes.h"
#include "ParticlePlay/Scene.h"
#include "ParticlePlay/BitmapFont.h"
#include "ParticlePlay/Input.h"
#include "ParticlePlay/GUI/GUI.h"

class TestScene : public ppScene{
private:
	ppBitmapFont* font;
	ppGUI* gui;
	int posx, posy;
public:
	void OnInit();
	void OnRender(SDL_Renderer* renderer, int delta);
	void OnUpdate(ppInput* input, int delta);
};

#endif