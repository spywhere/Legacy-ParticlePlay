#ifndef HIGHPASSFILTER_HEADER
#define HIGHPASSFILTER_HEADER

#include <ParticlePlay/IMS/Filter.hpp>

class ppHighPassFilter : public ppFilter {
protected:
	float gain, gainlf;
public:
	ppHighPassFilter();
	void InitFilter();
	float GetGain();
	float GetGainLF();
	void SetGain(float gain);
	void SetGainLF(float gainlf);
};

#endif
