#ifndef PHYSICS_HEADER
#define PHYSICS_HEADER

#include <ParticlePlay/Includes.hpp>

class ppPhysics{
protected:
	float ptm;
	b2World* world;
public:
	ppPhysics(float gx, float gy);
	b2World* GetWorld();
	// ppEffect* GetEffect();
	void Update(int delta);
	void UpdateAllBody();
	void SetPTM(float ptm);
	float GetPTM();
	float PixelToWorld(float pixel);
	float WorldToPixel(float world);
	~ppPhysics();
};

#endif
