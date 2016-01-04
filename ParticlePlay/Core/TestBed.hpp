#ifndef TESTBED_HEADER
#define TESTBED_HEADER

#include <vector>
#include <ParticlePlay/Includes.hpp>
#include <ParticlePlay/Core/Color.hpp>
#include <ParticlePlay/Core/State.hpp>
#include <ParticlePlay/Core/Input.hpp>
#include <ParticlePlay/Core/Physics.hpp>
#include <ParticlePlay/Graphics/BitmapFont.hpp>
#include <ParticlePlay/GUI/GUI.hpp>

class ppTestBed : public ppState{
protected:
	ppPhysics* physics;
	ppBitmapFont* font;
	ppGUI* gui;
	int help, cd, px, py, fx, fy, tx, ty;
	virtual void RenderCircle(b2Vec2 center, float radius, ppColor* color);
	virtual void RenderEdge(b2Vec2 v1, b2Vec2 v2, ppColor* color);
	virtual void RenderPolygon(std::vector<b2Vec2> vertices, ppColor* color);
	virtual void RenderChain(std::vector<b2Vec2> vertices, ppColor* color);
	virtual void RenderBody(b2Body* body);
public:
	virtual void OnInit();
	virtual void OnRender(ppGraphics* graphics, int delta);
	virtual void OnUpdate(ppInput* input, int delta);
};

#endif
