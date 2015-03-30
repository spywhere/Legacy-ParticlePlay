#ifndef LOWPASSFILTER_HEADER
#define LOWPASSFILTER_HEADER

#include <ParticlePlay/IMS/Filter.hpp>

class ppLowPassFilter : public ppFilter {
protected:
	float gainhf;
public:
	ppLowPassFilter(ppIMS* ims, ppFilterType type);
	void InitFilter();
	float GetGainHF();
	void SetGain(float gain);
	void SetGainHF(float gainhf);
};

#endif
