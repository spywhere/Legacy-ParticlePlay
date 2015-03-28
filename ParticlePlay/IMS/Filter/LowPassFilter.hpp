#ifndef LOWPASSFILTER_HEADER
#define LOWPASSFILTER_HEADER

#include <ParticlePlay/IMS/Filter.hpp>

class ppLowPassFilter : public ppFilter {
protected:
	float gain, gainhf;
public:
	ppLowPassFilter();
	void InitFilter();
	float GetGain();
	float GetGainHF();
	void SetGain(float gain);
	void SetGainHF(float gainhf);
};

#endif
