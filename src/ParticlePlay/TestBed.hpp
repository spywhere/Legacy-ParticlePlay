#ifndef TESTBED_HEADER
#define TESTBED_HEADER

#include "Includes.hpp"
#include "Color.hpp"
#include "State.hpp"
#include "BitmapFont.hpp"
#include "Input.hpp"
#include "Physics.hpp"
#include "GUI/GUI.hpp"
#include <vector>

class ppTestBed : public ppState{
protected:
	ppPhysics* physics;
	ppBitmapFont* font;
	ppGUI* gui;
	int help, cd, px, py, fx, fy, tx, ty;
	float ptm;
	virtual void RenderCircle(b2Vec2 center, float radius, ppColor* color);
	virtual void RenderEdge(b2Vec2 v1, b2Vec2 v2, ppColor* color);
	virtual void RenderPolygon(std::vector<b2Vec2> vertices, ppColor* color);
	virtual void RenderChain(std::vector<b2Vec2> vertices, ppColor* color);
public:
	virtual void OnInit();
	virtual void OnRender(SDL_Renderer* renderer, int delta);
	virtual void OnUpdate(ppInput* input, int delta);
};

#endif
