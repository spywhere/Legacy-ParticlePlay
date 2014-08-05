#ifndef TESTSCENE_HEADER
#define TESTSCENE_HEADER

#include "ParticlePlay/Includes.hpp"
#include "ParticlePlay/GUI/GUI.hpp"
#include "ParticlePlay/State.hpp"
#include "ParticlePlay/BitmapFont.hpp"
#include "ParticlePlay/Input.hpp"

class TestScene : public ppState{
protected:
	ppBitmapFont* font;
	ppGUI* gui;
	int posx, posy;
public:
	bool loading;
	int percent;

	void OnInit();
	void OnRender(SDL_Renderer* renderer, int delta);
	void OnUpdate(ppInput* input, int delta);
	static int RunLoader(void* data);
};

#endif
