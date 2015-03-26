#ifndef PHYSICSOBJECT_HEADER
#define PHYSICSOBJECT_HEADER

#include <ParticlePlay/ParticlePlay.hpp>
#include <vector>

class PhysicsObject {
protected:
	ppPhysics* physics;
	virtual void RenderCircle(b2Vec2 center, float radius, ppColor* color);
	virtual void RenderEdge(b2Vec2 v1, b2Vec2 v2, ppColor* color);
	virtual void RenderPolygon(std::vector<b2Vec2> vertices, ppColor* color);
	virtual void RenderChain(std::vector<b2Vec2> vertices, ppColor* color);
	virtual void RenderBody(b2Body* body);
	PhysicsObject(ppPhysics* physics);
};

#endif
