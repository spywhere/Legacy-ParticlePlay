#ifndef TESTBED_HEADER
#define TESTBED_HEADER

#include "Includes.h"
#include "State.h"
#include "BitmapFont.h"
#include "Input.h"
#include "Physics.h"
#include "GUI/GUI.h"
#include <vector>

class ppTestBed : public ppState{
private:
	ppPhysics* physics;
	ppBitmapFont* font;
	ppGUI* gui;
	int help, cd;
	void RenderCircle(b2Vec2 center, int radius, ppColor* color);
	void RenderEdge(b2Vec2 v1, b2Vec2 v2, ppColor* color);
	void RenderPolygon(std::vector<b2Vec2> vertices, ppColor* color);
	void RenderChain(std::vector<b2Vec2> vertices, ppColor* color);
public:
	void OnInit();
	void OnRender(SDL_Renderer* renderer, int delta);
	void OnUpdate(ppInput* input, int delta);
};

#endif