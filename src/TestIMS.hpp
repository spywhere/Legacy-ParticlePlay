#ifndef TESTIMS_HEADER
#define TESTIMS_HEADER

#include "ParticlePlay/Includes.hpp"
#include "ParticlePlay/GUI/GUI.hpp"
#include "ParticlePlay/State.hpp"
#include "ParticlePlay/Input.hpp"

class TestIMS : public ppState{
protected:
	ppGUI* gui;
	void DrawRect(int x, int y, int w, int h);
	void DrawFillRect(int x, int y, int w, int h);
public:
	void OnInit();
	void OnRender(SDL_Renderer* renderer, int delta);
	void OnUpdate(ppInput* input, int delta);
};

#endif
