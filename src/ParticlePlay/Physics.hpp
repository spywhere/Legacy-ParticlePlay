#ifndef PHYSICS_HEADER
#define PHYSICS_HEADER

#include "Includes.hpp"

class ppPhysics{
protected:
	b2World* world;
	int fps;
public:
	ppPhysics(int fps, float gx, float gy);
	b2World* GetWorld();
	// ppEffect* GetEffect();
	void Update();
	void UpdateAllBody();
	~ppPhysics();
};

#endif
