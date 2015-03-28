#ifndef FILTER_HEADER
#define FILTER_HEADER

#include <ParticlePlay/Includes.hpp>

enum class ppFilterType {
	LOW_PASS, BAND_PASS, HIGH_PASS
};

class ppFilter {
protected:
	bool init;
	bool supported;
	ALuint filterID;
public:
	ppFilter();
	virtual ~ppFilter();
	virtual void InitFilter();
	virtual bool IsSupported();
	virtual ALuint GetFilterID();
};

#endif
