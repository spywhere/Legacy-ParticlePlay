#ifndef PHYSICSOBJECT_HEADER
#define PHYSICSOBJECT_HEADER

#include <ParticlePlay/ParticlePlay.hpp>
#include <vector>

class PhysicsObject {
protected:
	bool debugView;
	ppPhysics* physics;
	virtual void RenderCircle(ppGraphics* graphics, b2Vec2 center, float radius, ppColor* color);
	virtual void RenderEdge(ppGraphics* graphics, b2Vec2 v1, b2Vec2 v2, ppColor* color);
	virtual void RenderPolygon(ppGraphics* graphics, std::vector<b2Vec2> vertices, ppColor* color);
	virtual void RenderChain(ppGraphics* graphics, std::vector<b2Vec2> vertices, ppColor* color);
	virtual void RenderBody(ppGraphics* graphics, b2Body* body);
	PhysicsObject(ppPhysics* physics);
public:
	void SetDebugView(bool debugView);
};

#endif
